## Solid Design Principle 
- S : Single Responsibility Principle 
- O : Open Close Principle
- L : Liskov Substitution Principle
- I : Interface Segregation Principle 
- D : Dependency Inversion Principle

# S : Single Responsibility Principle 
- A class should have only one reason to change.
- A class should do only one thing 
- We have single class which is handling the calculate price , save to db logic , print invoice 
  so if needed to change one of the class methods then we have to touch the entire class, which violates the SRP.

- So to avoid this we make multiple small classes which performs the specific each method ( responsibility ) and use composition for the same.


# O : Open Close Principle
- A class should be open for extension but closed for modification.
- Open close principle can be applied using the polymorphism, abstract classes and inheritance.