
# SOLID Principles — Interview Q&A Cheatsheet
> SDE-1/2 Interview Prep | Abhay | 2026

---

## S — Single Responsibility Principle (SRP)

### Q1. This class handles fetching user from DB, sending welcome email, and logging user activity. What's violated and why?

**Principle:** SRP

**Why it's violated:**
SRP says a class should have **only one reason to change**. This class has three:
- DB schema changes → touch this class
- Email provider changes → touch this class
- Logging strategy changes → touch this class

Three independent axes of change = SRP violation.

**Fix:** Split into `UserRepository`, `EmailService`, `ActivityLogger` — each with one reason to change.

> ⚠️ Common mistake: saying "it does 3 things" — that's the surface. The real answer is **"3 reasons to change."**

---

## O — Open/Closed Principle (OCP)

### Q2. This method has if/else for welcome, reset, invoice email types. Which principle is at risk when adding a new type?

```ts
sendEmail(type: string) {
  if (type === "welcome") { ... }
  else if (type === "reset") { ... }
  else if (type === "invoice") { ... }
}
```

**Principle:** OCP

**Why it's violated:**
Every new email type forces you to **go back into existing working code** and add an `else if`. You're modifying tested, deployed logic instead of extending it.

**Fix:**
```ts
interface EmailSender {
  send(to: string): void
}
class WelcomeEmail implements EmailSender { ... }
class ResetEmail implements EmailSender { ... }
class InvoiceEmail implements EmailSender { ... }
```
Adding a new type = new class. Zero changes to existing code.

> ⚠️ Complete answer includes a **factory/registry** that maps the type string to the right implementation.

---

## L — Liskov Substitution Principle (LSP)

### Q3. Penguin extends Bird but throws an error on fly(). What's violated?

```ts
class Bird { fly() { ... } }
class Penguin extends Bird {
  fly() { throw new Error("Penguins can't fly") }
}
```

**Principle:** LSP

**Why it's violated:**
Not a signature issue — the signature is fine. The violation is **behavioral substitution**. Any code that trusts `Bird.fly()` will get a runtime exception when handed a `Penguin`. The subtype broke the base contract.

**Fix:** Restructure the abstraction — don't patch the child:
```ts
interface Bird { }
interface FlyingBird extends Bird { fly(): void }

class Sparrow implements FlyingBird { fly() { ... } }
class Penguin implements Bird { } // never promises fly()
```

> ⚠️ LSP violations are almost always a signal that the **inheritance hierarchy is wrong**, not that the child class needs fixing.

---

## I — Interface Segregation Principle (ISP)

### Q4. EmailNotifier is forced to implement sendSMS and sendPush and throws errors. What's violated?

```ts
interface Notifier {
  sendEmail(msg: string): void
  sendSMS(msg: string): void
  sendPush(msg: string): void
}
class EmailNotifier implements Notifier {
  sendEmail(msg: string) { ... }
  sendSMS(msg: string) { throw new Error("Not supported") }
  sendPush(msg: string) { throw new Error("Not supported") }
}
```

**Principle:** ISP

**Why it's violated:**
`EmailNotifier` is forced to depend on methods it will never use.

**Fix:** Split the fat interface:
```ts
interface EmailNotifier { sendEmail(msg: string): void }
interface SMSNotifier   { sendSMS(msg: string): void   }
interface PushNotifier  { sendPush(msg: string): void  }

class EmailService implements EmailNotifier { sendEmail(msg) { ... } }
class SMSService   implements SMSNotifier   { sendSMS(msg)   { ... } }

// A class can implement multiple if it genuinely supports both
class OmniNotifier implements EmailNotifier, SMSNotifier {
  sendEmail(msg) { ... }
  sendSMS(msg)   { ... }
}
```

> ⚠️ Never name a class and interface the same thing — it won't compile.

**One-liner for interviews:**
> "No client should be forced to depend on methods it does not use."

---

## D — Dependency Inversion Principle (DIP)

### Q5. UserService directly instantiates MySQLUserRepository. What's violated?

```ts
class UserService {
  private repo = new MySQLUserRepository() // ❌
}
```

**Principle:** DIP (root cause) + OCP (consequence)

**Why it's violated:**
`UserService` (high level) is directly coupled to `MySQLUserRepository` (low level concrete). DIP says both should depend on an **abstraction**.

**Fix:**
```ts
interface UserRepository {
  getUser(id: string): User
  saveUser(user: User): void
}
class MySQLUserRepository implements UserRepository { ... }
class MongoUserRepository  implements UserRepository { ... }

class UserService {
  constructor(private repo: UserRepository) {} // injected abstraction
}
```

Switching DB = new class, zero changes to `UserService`.

> ⚠️ DIP violations almost always **cause OCP violations as a side effect**. Call DIP as the root cause, OCP as the consequence — not two equal violations.

---

## Combined Violation — Real World

### Q6. How many SOLID violations in this KYC service?

```ts
class KYCService {
  async verifyUser(userId: string) {
    const user = await db.query(`SELECT * FROM users WHERE id = ${userId}`)
    if (user.type === "individual") { /* 50 lines */ }
    else if (user.type === "business") { /* 50 lines */ }
    await mailer.send(user.email, "KYC done")
    await logger.log(`KYC verified: ${userId}`)
  }
}
```

**Three violations:**

| Principle | Violation | Production Risk |
|-----------|-----------|-----------------|
| **SRP** | 4 responsibilities: verification, DB, email, logging | Change in email provider = touching KYC logic = compliance incident |
| **OCP** | New user type = crack open existing method | Regression risk on individual/business flows every sprint |
| **DIP** | Direct coupling to `db`, `mailer`, `logger` | Cannot unit test without real DB/mailer. Also: SQL injection via string interpolation |

**Fix structure:**
```ts
class KYCService {
  constructor(
    private userRepo: UserRepository,
    private verifierFactory: VerifierFactory,
    private notifier: NotificationService,
    private logger: AuditLogger
  ) {}

  async verifyUser(userId: string) {
    const user = await this.userRepo.findById(userId) // parameterized query
    const verifier = this.verifierFactory.getFor(user.type)
    await verifier.verify(user)
    await this.notifier.send(user.email, "KYC done")
    await this.logger.log(`KYC verified: ${userId}`)
  }
}
```

> ⚠️ Don't confuse bugs (null email, premature logging) with SOLID violations. SOLID is about **design structure**, not runtime null checks.

---

## Conceptual Questions

### Q7. SRP vs ISP — what's the actual difference?

Both are about keeping things focused — but at different layers:

| | SRP | ISP |
|---|---|---|
| **Applies to** | Classes | Interfaces |
| **Asks** | Does this class have one reason to change? | Does this interface force clients to implement what they don't need? |
| **Problem** | Class doing too many things | Interface promising too many things |

**One line:**
> SRP is about **how you build a class**. ISP is about **how you design the contract** that class signs.

---

### Q8. Which SOLID principle gives most value in production? Which is most misapplied?

**Most valuable: SRP**
Not because it's simple — because it's **foundational**. Violate SRP and OCP/DIP violations follow automatically. Fix SRP and the other violations often dissolve.

**Most misapplied: DIP**
Developers misread it as *"every class must have an interface."* Wrong.

DIP means depend on abstractions **where the implementation is likely to change**. A `UserController` calling `UserService` in a stable CRUD app doesn't need `IUserService`. That's cargo cult DIP.

> Create an interface when you have **two or more implementations** or a **genuine reason to swap**. One class, one implementation, stable forever — no interface needed.

---

### Q9. ReportGenerator has if/else for pdf/excel/csv. New formats XML and JSON coming next sprint. Fix it.

**Violations:** SRP + OCP

**Production-ready fix:**
```ts
interface ReportExporter {
  export(report: Report): Buffer
}

class PDFExporter   implements ReportExporter { export(r) { ... } }
class ExcelExporter implements ReportExporter { export(r) { ... } }
class CSVExporter   implements ReportExporter { export(r) { ... } }

class ExporterRegistry {
  private exporters = new Map<string, ReportExporter>([
    ["pdf",   new PDFExporter()],
    ["excel", new ExcelExporter()],
    ["csv",   new CSVExporter()],
  ])

  getExporter(format: string): ReportExporter {
    const exporter = this.exporters.get(format)
    if (!exporter) throw new Error(`Unsupported format: ${format}`)
    return exporter
  }
}

class ReportGenerator {
  constructor(private registry: ExporterRegistry) {}

  generate(report: Report, format: string): Buffer {
    return this.registry.getExporter(format).export(report)
  }
}
```

**Adding XML next sprint — zero existing files touched:**
```ts
class XMLExporter implements ReportExporter { export(r) { ... } }
exporters.set("xml", new XMLExporter()) // one line
```

---

### Q10. Colleague created 47 interfaces for a CRUD app claiming "fully SOLID compliant." Your review comment?

**Principle misused:** DIP

**Review comment:**
> "SOLID is a guideline, not a checklist. DIP doesn't mean every class needs an interface — it means depend on abstractions where the implementation is likely to change or be swapped. In a stable CRUD app, `UserService` won't be swapped. `IUserService` adds zero value and doubles the files a new developer has to navigate. Apply DIP at genuine volatility points: external services, DB layer, third-party integrations. Remove interfaces that exist only for compliance theatre."

> ⚠️ Rule of thumb: **If you can't name two concrete implementations right now, you probably don't need the interface.**

---

## Quick Reference — All 5 Principles

| Principle | One Line | Violation Signal | Fix |
|-----------|----------|------------------|-----|
| **SRP** | One reason to change | Class touches multiple domains | Split into focused classes |
| **OCP** | Extend, don't modify | Adding feature = editing existing code | Abstractions + new implementations |
| **LSP** | Subtypes must honor base contract | Child throws errors or weakens behaviour | Restructure hierarchy |
| **ISP** | Don't force unused methods | Interface has methods some implementors throw on | Split fat interfaces |
| **DIP** | Depend on abstractions | `new ConcreteClass()` inside high-level module | Constructor injection + interfaces |

---

*Next: Design Patterns (Strategy, Factory, Observer, Decorator...)*