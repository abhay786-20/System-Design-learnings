// ─── Core contract ─────────────────────────────────────────
interface NotificationChannel {
  send(message: string, recipient: string): void
}

// ─── Concrete channels ─────────────────────────────────────
class EmailChannel implements NotificationChannel {
  send(message: string, recipient: string): void {
    console.log(`[EMAIL] to ${recipient}: ${message}`)
  }
}

class SMSChannel implements NotificationChannel {
  send(message: string, recipient: string): void {
    console.log(`[SMS] to ${recipient}: ${message}`)
  }
}

class PushChannel implements NotificationChannel {
  send(message: string, recipient: string): void {
    console.log(`[PUSH] to ${recipient}: ${message}`)
  }
}

// ─── New channels — zero existing files touched ────────────
class WhatsAppChannel implements NotificationChannel {
  send(message: string, recipient: string): void {
    console.log(`[WHATSAPP] to ${recipient}: ${message}`)
  }
}

class SlackChannel implements NotificationChannel {
  send(message: string, recipient: string): void {
    console.log(`[SLACK] to ${recipient}: ${message}`)
  }
}

// ─── Registry — injectable, not static ────────────────────
class NotificationRegistry {
  private channels = new Map<string, NotificationChannel>([
    ["email",    new EmailChannel()],
    ["sms",      new SMSChannel()],
    ["push",     new PushChannel()],
    ["whatsapp", new WhatsAppChannel()],
    ["slack",    new SlackChannel()],
  ])

  getChannel(type: string): NotificationChannel {
    const channel = this.channels.get(type)
    if (!channel) {
      throw new Error(`Unsupported notification type: "${type}"`)
    }
    return channel
  }

  register(type: string, channel: NotificationChannel): void {
    this.channels.set(type, channel)
  }
}

// ─── High level service ────────────────────────────────────
class NotificationService {
  constructor(private registry: NotificationRegistry) {}

  send(type: string, message: string, recipient: string): void {
    const channel = this.registry.getChannel(type)
    channel.send(message, recipient)
  }
}

// ─── Composition root ──────────────────────────────────────
const registry = new NotificationRegistry()
const notificationService = new NotificationService(registry)

notificationService.send("email",    "Payment confirmed", "user@gmail.com")
notificationService.send("whatsapp", "Your OTP is 1234",  "+919876543210")
notificationService.send("slack",    "Deploy successful", "#engineering")