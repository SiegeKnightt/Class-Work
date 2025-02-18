DROP SCHEMA IF EXISTS Pizzeria;
CREATE SCHEMA Pizzeria;
USE Pizzeria;

CREATE TABLE IF NOT EXISTS customer (
	CustomerID varchar(20) NOT NULL,
    CustomerFName varchar(20),
    CustomerLName varchar(20),
    CustomerPhone varchar(20),
    CustomerStreet varchar(20),
    CustomerCity varchar(20),
    CustomerState varchar(20),
    CustomerZip varchar(20),
    PRIMARY KEY (CustomerID)
);

CREATE TABLE IF NOT EXISTS orderpizza (
	OrderID varchar(20) NOT NULL,
    OrderCost varchar(20),
    OrderType varchar(20),
    OrderTimeStamp DATE,
    OrderState varchar(20),
    OrderPrice varchar(20),
    OrderCustID varchar(20),
    PRIMARY KEY (OrderID),
    FOREIGN KEY (OrderCustID) REFERENCES customer(CustomerID)
);

CREATE TABLE IF NOT EXISTS discount (
	DiscountID INT NOT NULL,
    DiscountType INT, -- 1 = percent, 0 = fixed amount
    DiscountName varchar(20),
    DiscountAmount DOUBLE,
    PRIMARY KEY (DiscountID)
);

CREATE TABLE IF NOT EXISTS topping (
	ToppingID varchar(20) NOT NULL PRIMARY KEY,
    ToppingName varchar(20),
    ToppingPricePerUnit varchar(20),
    ToppingCostPerUnit varchar(20),
    ToppingInventory varchar(20),
    ToppingMinimum varchar(20),
    ToppingSmallUnits varchar(20),
    ToppingMediumUnits varchar(20),
    ToppingLargeUnits varchar(20),
    ToppingXLargeUnits varchar(20)
);

CREATE TABLE IF NOT EXISTS basepizza (
	BasePizzaSize varchar(20) NOT NULL,
    BasePizzaCrust varchar(20) NOT NULL,
    BasePizzaPrice varchar(20),
    BasePizzaCost varchar(20),
    PRIMARY KEY (BasePizzaSize,BasePizzaCrust)
);

CREATE TABLE IF NOT EXISTS pizzaorder(
	PizzaOrderID varchar(20) NOT NULL PRIMARY KEY,
    PizzaOrderOrderID varchar(20),
    PizzaOrderPizzaSize varchar(20),
    PizzaOrderPizzaCrust varchar(20),
    PizzaOrderPizzaState varchar(20),
    PizzaOrderTime varchar(20),
    PizzaOrderPrice varchar(20),
    PizzaOrderCost varchar(20),
    FOREIGN KEY (PizzaOrderOrderID) REFERENCES orderpizza(OrderID),
    FOREIGN KEY (PizzaOrderPizzaSize,PizzaOrderPizzaCrust) REFERENCES basepizza(BasePizzaSize,BasePizzaCrust)
    
);

CREATE TABLE IF NOT EXISTS pizzadiscount(
	PizzaOrderID varchar(20) NOT NULL,
    DiscountID INT NOT NULL,
	PRIMARY KEY (PizzaOrderID,DiscountID),
    FOREIGN KEY (PizzaOrderID) REFERENCES pizzaorder(PizzaOrderID),
    FOREIGN KEY (DiscountID) REFERENCES discount(DiscountID)
);

CREATE TABLE IF NOT EXISTS ordertopping(
	PizzaOrderID varchar(20) NOT NULL,
    ToppingID varchar(20),
    ExtraTopping INT NOT NULL,
    PRIMARY KEY (PizzaOrderID, ToppingID),
    FOREIGN KEY (PizzaOrderID) REFERENCES pizzaorder(PizzaOrderID),
    FOREIGN KEY (ToppingID) REFERENCES topping(ToppingID)
);

CREATE TABLE IF NOT EXISTS orderdiscount (
	OrderID varchar(20) NOT NULL,
    DiscountID INT,
    PRIMARY KEY (OrderID, DiscountID),
    FOREIGN KEY (OrderID) REFERENCES orderpizza(OrderID),
    FOREIGN KEY (DiscountID) REFERENCES discount(DiscountID)
);

CREATE TABLE IF NOT EXISTS delivery (
	OrderID varchar(20) NOT NULL,
    CustomerID varchar(20),
    PRIMARY KEY (OrderID),
    FOREIGN KEY (OrderID) REFERENCES orderpizza(OrderID),
    FOREIGN KEY (CustomerID) REFERENCES customer(CustomerID)
);

CREATE TABLE IF NOT EXISTS pickup (
	OrderID varchar(20) NOT NULL,
    CustomerID varchar(20),
    PRIMARY KEY (OrderID),
    FOREIGN KEY (OrderID) REFERENCES orderpizza(OrderID),
    FOREIGN KEY (CustomerID) REFERENCES customer(CustomerID)
);

CREATE TABLE IF NOT EXISTS dinein (
    OrderID varchar(20) NOT NULL,
    TableNum INT NOT NULL,
    PRIMARY KEY (OrderID),
    FOREIGN KEY (OrderID) REFERENCES orderpizza(OrderID)
);