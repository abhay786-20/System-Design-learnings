interface OrderObserver {
    update(order: Order): Promise<void>;
}

class Order {
    email!: string;
    phone!: string;
    slackChannel!: string;
}

class OrderSubject {
    private observers: OrderObserver[] = [];

    subscribe(observer: OrderObserver): void {
        this.observers.push(observer);
    }

    unsubscribe(observer: OrderObserver): void {
        this.observers = this.observers.filter(
            obs => obs !== observer
        );
    }

    async notify(order: Order): Promise<void> {
        await Promise.all(
            this.observers.map(observer =>
                observer.update(order)
            )
        );
    }
}

class EmailOrderObserver implements OrderObserver {
    async update(order: Order): Promise<void> {
        console.log(`Emailing order details to ${order.email}`);
    }
}

class SMSOrderObserver implements OrderObserver {
    async update(order: Order): Promise<void> {
        console.log(`Sending order details to ${order.phone}`);
    }
}

class SlackOrderObserver implements OrderObserver {
    async update(order: Order): Promise<void> {
        console.log(
            `Posting order details to ${order.slackChannel}`
        );
    }
}

async function main() {
    const orderSubject = new OrderSubject();

    orderSubject.subscribe(new EmailOrderObserver());
    orderSubject.subscribe(new SMSOrderObserver());
    orderSubject.subscribe(new SlackOrderObserver());

    const order = new Order();
    order.email = "user@example.com";
    order.phone = "+919876543210";
    order.slackChannel = "#engineering";

    await orderSubject.notify(order);
}

main().catch(console.error);