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
- Use abstract classes and interfaces to achieve this. 
- Save to db 

# L : Liskov Substitution Principle
- A class should be substitutable for its child class.
- Liskov Substitution Principle can be applied using the polymorphism, abstract classes and inheritance.
- A place where we can use the base class , we can use the derived class as well , there only one thing we need to do is we don't override the method of the base class.
- if a child class is narrowing the functionality of the parent class then we can use the child class as a abstract class and can make a class like the super-base class .
- Account example : FD , Saving , current etc .
- Child class should behave like the parent class , so we can use the child class as a parent class .

- Guidelines for LSP
    - Signature Rule : Methods of the parent ,argument types , a child class should also have the same signature as the parent class.
        - Method signature : argument types
        - Return type - return type must be same or of the child class, not the grand parent class.
        Covariance : If like return types return the narrower type , then it is called covariance.
        - Exception Error : Child class can throw the exception of the parent class or the narrower type 

    - Property Rule : Properties of the parent class , a child class should also have the same properties as the parent class.
        - class Invariant : Class invariants are properties that are always true for a class.
             - Child should follow or strengthen the parent class invariants.
             - Ex - Accoount class , balance should be always greater than or equals to zero,  child cheat class breaks the rule.

        - History Constraints : A child class should not violate the parent class history constraints.
            - Ex - BankAccount class , withdrawal should not be allowed from Fixed Deposit Account.

    - Method Rule : Conditons should follow for the parent class , a child class should also follow the same conditions.
        - PreCondition Rule : Condition to follow before running the method.
        - PostCondition Rule : A child class should not violate the parent class post conditions.

# Interface Segregation Principle
- Many client specific interfaces are better than one general purpose interface.
- Client should not be forced to depend on interface that it does not use.
- Shape 2d and 3d shapes are examples of interfaces.
- ISP : Interface Segregation Principle
    - Separate interface for 2D shapes
        - Square
        - Rectangle

    - Separate interface for 3D shapes
        - Cube

    - ISP Violated : Square and Rectangle implement only the 2D interface
        - Square
            - area
            - volume

        - Rectangle
            - area
            - volume

    - ISP Adhered : Cube implements the 3D interface
        - Cube
            - area  
            - volume  
            
# Dependency Inversion Principle
- High level modules should not depend on low level modules. Both should depend on abstractions.
- Abstractions should not depend on details. Details should depend on abstractions.
- DIP : Dependency Inversion Principle
    - Abstraction : Abstractions are modules that provide a level of indirection.
    - Dependency : Dependencies are modules that depend on abstractions.
    - DIP Violated : Bank Account class , BankAccount class depends on BankAccountDetail class
        - BankAccount
            - BankAccountDetail
                - BankAccountDetail
                    -BankAccountDetail
                        - BankAccountDetail
                            - ...

    - DIP Adhered : Bank Account class , BankAccount class depends on BankAccountDetail class
        - BankAccount
            - BankAccountDetail
                - BankAccountDetail
                    -BankAmountDetail
                        - BankAmountDetail
                            - ...