// ─── Types ─────────────────────────────────────────────────
interface OTPRecord {
  phone: string
  otp: string
  createdAt: Date
}

// ─── Abstractions (interfaces not classes) ─────────────────
interface OTPRepository {
  save(record: OTPRecord): Promise<void>
}

interface SMSProvider {
  send(phone: string, message: string): Promise<void>
}

interface CacheProvider {
  set(key: string, value: string, ttl: number): Promise<void>
  get(key: string): Promise<string | null>  // get was missing
}

// ─── Concrete implementations ──────────────────────────────
class PostgresOTPRepository implements OTPRepository {
  private pool = new Pool()

  async save(record: OTPRecord): Promise<void> {
    await this.pool.query(
      'INSERT INTO otp_records (phone, otp, created_at) VALUES ($1, $2, $3)',
      [record.phone, record.otp, record.createdAt]
    )
  }
}

class TwilioSMSProvider implements SMSProvider {
  private client = new Twilio(
    process.env.TWILIO_ACCOUNT_SID!,
    process.env.TWILIO_AUTH_TOKEN!
  )

  async send(phone: string, message: string): Promise<void> {
    await this.client.messages.create({
      body: message,
      from: process.env.TWILIO_NUMBER!,
      to: phone
    })
  }
}

class RedisCacheProvider implements CacheProvider {
  private client = new Redis(process.env.REDIS_URL!)

  async set(key: string, value: string, ttl: number): Promise<void> {
    await this.client.set(key, value, 'EX', ttl)
  }

  async get(key: string): Promise<string | null> {
    return await this.client.get(key)
  }
}

// ─── High level service — depends on abstractions only ─────
class OTPService {
  constructor(
    private db: OTPRepository,      // interface
    private sms: SMSProvider,       // interface
    private cache: CacheProvider    // interface
  ) {}

  async sendOTP(phone: string): Promise<void> {
    const otp = Math.floor(100000 + Math.random() * 900000).toString()
    await this.cache.set(`otp:${phone}`, otp, 300)
    await this.sms.send(phone, `Your OTP is ${otp}`)
    await this.db.save({ phone, otp, createdAt: new Date() })
  }

  async verifyOTP(phone: string, otp: string): Promise<boolean> {
    const cached = await this.cache.get(`otp:${phone}`)
    return cached === otp
  }
}

// ─── Composition root — wire it all up ─────────────────────
const otpService = new OTPService(
  new PostgresOTPRepository(),
  new TwilioSMSProvider(),
  new RedisCacheProvider()
)