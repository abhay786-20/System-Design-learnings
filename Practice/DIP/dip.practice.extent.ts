class PaymentService {
  async processPayment(orderId: string, amount: number) {
    const razorpay = new Razorpay({
      key_id: process.env.RAZORPAY_KEY,
      key_secret: process.env.RAZORPAY_SECRET
    })

    const order = await razorpay.orders.create({
      amount: amount * 100,
      currency: 'INR',
      receipt: orderId
    })

    return order
  }
}


interface Payment {
    orderId: string
    amount: number
}

interface PaymentGateway {
    processPayment(payment: Payment): Promise<void>
}

class RazorpayPaymentGateway implements PaymentGateway {
    private razorpay: Razorpay

    constructor(keyId: string, keySecret: string) {
        this.razorpay = new Razorpay({
            key_id: keyId,
            key_secret: keySecret
        })
    }

    async processPayment(payment: Payment): Promise<void> {
        const order = await this.razorpay.orders.create({
            amount: payment.amount * 100,
            currency: 'INR',
            receipt: payment.orderId
        })
    }
}

class StripePaymentGateway implements PaymentGateway {
    private stripe: Stripe

    constructor(keyId: string, keySecret: string) {
        this.stripe = new Stripe(keyId, keySecret)
    }

    async processPayment(payment: Payment): Promise<void> {
        const order = await this.stripe.orders.create({
            amount: payment.amount * 100,
            currency: 'INR',
            receipt: payment.orderId
        })
    }
}


class PaymentService {
    private paymentGateway: PaymentGateway

    constructor(paymentGateway: PaymentGateway) {
        this.paymentGateway = paymentGateway
    }

    async processPayment(orderId: string, amount: number) {
        await this.paymentGateway.processPayment({
            orderId,
            amount
        })
    }
}   


const paymentService = new PaymentService(new RazorpayPaymentGateway(
    process.env.RAZORPAY_KEY,
    process.env.RAZORPAY_SECRET
))

paymentService.processPayment('1234', 100)

const paymentServiceStripe = new PaymentService(new StripePaymentGateway(
    process.env.STRIPE_KEY,
    process.env.STRIPE_SECRET
))

paymentService.processPayment('1234', 100)  