USE Pizzeria;

INSERT INTO topping (
	ToppingID, 
    ToppingName, 
    ToppingPricePerUnit, 
    ToppingCostPerUnit, 
    ToppingInventory, 
    ToppingMinimum, 
    ToppingSmallUnits, 
    ToppingMediumUnits, 
    ToppingLargeUnits, 
    ToppingXLargeUnits)
VALUES 
	('101', 'Pepperoni', 1.25, 0.2, 100, 50, 2, 2.75, 3.5, 4.5),
	('102', 'Sausage', 1.25, 0.15, 100, 50, 2.5, 3, 3.5, 4.25),
	('103', 'Ham', 1.5, 0.15, 78, 25, 2, 2.5, 3.25, 4),
	('104', 'Chicken', 1.75, 0.25, 56, 25, 1.5, 2, 2.25, 3),
	('105', 'Green Pepper', 0.5, 0.02, 79, 25, 1, 1.5, 2, 2.5),
	('106', 'Onion', 0.5, 0.02, 85, 25, 1, 1.5, 2, 2.75),
	('107', 'Roma Tomato', 0.75, 0.03, 86, 10, 2, 3, 3.5, 4.5),
	('108', 'Mushrooms', 0.75, 0.1, 52, 50, 1.5, 2, 2.5, 3),
	('109', 'Black Olives', 0.6, 0.1, 39, 25, 0.75, 1, 1.5, 2),
	('110', 'Pineapple', 1, 0.25, 15, 0, 1, 1.25, 1.75, 2),
	('111', 'Jalapenos', 0.5, 0.05, 64, 0, 0.5, 0.75, 1.25, 1.75),
	('112', 'Banana Peppers', 0.5, 0.05, 36, 0, 0.6, 1, 1.3, 1.75),
	('113', 'Regular Cheese', 0.5, 0.12, 250, 50, 2, 3.5, 5, 7),
	('114', 'Four Cheese Blend', 1, 0.15, 150, 25, 2, 3.5, 5, 7),
	('115', 'Feta Cheese', 1.5, 0.18, 75, 0, 1.75, 3, 4, 5.5),
	('116', 'Goat Cheese', 1.5, 0.2, 54, 0, 1.6, 2.75, 4, 5.5),
	('117', 'Bacon', 1.5, 0.25, 89, 0, 1, 1.5, 2, 3);
    
INSERT INTO discount (
	DiscountID, 
    DiscountType, 
    DiscountName,
    DiscountAmount)
VALUES 
	('100', 1, 'Employee', 0.15),
	('101', 0, 'Lunch Special Medium', 1.00),
	('102', 0, 'Lunch Special Large', 2.00),
	('103', 0, 'Specialty Pizza', 1.50),
	('104', 0, 'Happy Hour', 0.10),
	('105', 1, 'Gameday Special', 0.20),
    ('106', 0, 'None', 0.00);

    
INSERT INTO basepizza (
	BasePizzaSize, 
    BasePizzaCrust, 
    BasePizzaPrice, 
    BasePizzaCost)
VALUES 
	('Small', 'Thin', 3, 0.5),
	('Small', 'Original', 3, 0.75),
	('Small', 'Pan', 3.5, 1),
	('Small', 'Gluten-Free', 4, 2),
	('Medium', 'Thin', 5, 1),
	('Medium', 'Original', 5, 1.5),
	('Medium', 'Pan', 6, 2.25),
	('Medium', 'Gluten-Free', 6.25, 3),
	('Large', 'Thin', 8, 1.25),
	('Large', 'Original', 8, 2),
	('Large', 'Pan', 9, 3),
	('Large', 'Gluten-Free', 9.5, 4),
	('XLarge', 'Thin', 10, 2),
	('XLarge', 'Original', 10, 3),
	('XLarge', 'Pan', 11.5, 4.5),
	('XLarge', 'Gluten-Free', 12.5, 6);

INSERT INTO customer (
	CustomerID,
    CustomerFName,
    CustomerLName,
    CustomerPhone,
    CustomerStreet,
    CustomerCity,
    CustomerState,
    CustomerZip
)
VALUES
	('100','Andrew', 'Wilkes-Krier','864-254-5861','115 Party Blvd', 'Anderson', 'SC', '29621'),
    ('101','Matt', 'Engers','864-474-9953', NULL, NULL, NULL, NULL),
    ('102','Frank', 'Turner','864-232-8944','6745 Wessex St', 'Anderson', 'SC', '29621'),
    ('103','Milo', 'Auckerman','864-878-5679','8879 Suburban Home', 'Anderson', 'SC', '29621');
    
INSERT INTO orderpizza (
	OrderID,
    OrderCost,
    OrderType,
    OrderTimeStamp,
    OrderState,
    OrderPrice,
    OrderCustID
)
VALUES
	-- use lunch special large discount
    -- table 21
	('1001', '3.68', 'dinein', '2023-03-05 12:03:00', '1', '20.75', NULL),
    
    -- use lunch special medium and specialty pizza discounts
    -- table 4
    ('1002', '4.63', 'dinein', '2023-04-03 12:05:00', '1', '19.78', NULL),
    
    -- no discount
    ('1003', '19.80', 'pickup', '2023-03-03 21:30:00', '1', '89.28', '100'),
    
    -- use gameday special and specialty pizza discount on ham and pineapple
    ('1004', '23.62', 'delivery', '2023-04-20 19:11:00', '1', '86.19', '100'),
    
    -- use specialty pizza discount
    ('1005', '7.88', 'pickup', '2023-03-02 17:30:00', '1', '27.45', '101'),
    
    -- no discount
    ('1006', '4.24', 'delivery', '2023-03-02 18:17:00', '1', '25.81', '102'),
    
    -- use employee discount
    ('1007', '6.00', 'Delivery', '2023-04-13 20:32:00', '1', '37.25', '103');
    
INSERT INTO dinein (OrderID, TableNum)
SELECT OrderID, 21 AS TableNum
FROM orderpizza
WHERE OrderID = 1001;
INSERT INTO dinein (OrderID, TableNum)
SELECT OrderID, 4 AS TableNum
FROM orderpizza
WHERE OrderID = 1002;

INSERT INTO delivery (OrderID, CustomerID)
SELECT OrderID, OrderCustID
FROM orderpizza
WHERE OrderID = 1004 OR OrderID = 1006 OR OrderID = 1007;

INSERT INTO pickup (OrderID, CustomerID)
SELECT OrderID, OrderCustID
FROM orderpizza
WHERE OrderID = 1003 OR OrderID = 1005;

INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1001', DiscountID FROM discount
WHERE DiscountID = '102';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1002', DiscountID FROM discount
WHERE DiscountID = '101';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1002', DiscountID FROM discount
WHERE DiscountID = '103';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1003', DiscountID FROM discount
WHERE DiscountID = '106';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1004', DiscountID FROM discount
WHERE DiscountID = '105';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1004', DiscountID FROM discount
WHERE DiscountID = '103';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1005', DiscountID FROM discount
WHERE DiscountID = '103';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1006', DiscountID FROM discount
WHERE DiscountID = '106';
INSERT INTO orderdiscount (OrderID, DiscountID)
SELECT '1007', DiscountID FROM discount
WHERE DiscountID = '100';

INSERT INTO pizzaorder (
	PizzaOrderID, 
    PizzaOrderOrderID, 
    PizzaOrderPizzaSize, 
    PizzaOrderPizzaCrust, 
    PizzaOrderPizzaState, 
    PizzaOrderTime, 
    PizzaOrderPrice, 
    PizzaOrderCost
)
VALUES
	(101, 1001, 'Large', 'Thin', '1', '2023-03-05 12:03:00', '20.75', '3.68'),
    (102, 1002, 'Medium', 'Pan', '1','2023-04-03 12:05:00', '12.85', '3.23'),
    (103, 1002, 'Small', 'Original', '1', '2023-04-03 12:05:00', '6.93', '1.40'),
    (104, 1003, 'Large', 'Original', '1', '2023-03-03 9:30:00','14.88','3.30'),
    (105, 1003, 'Large', 'Original', '1', '2023-03-03 9:30:00','14.88','3.30'),
    (106, 1003, 'Large', 'Original', '1', '2023-03-03 9:30:00','14.88','3.30'),
    (107, 1003, 'Large', 'Original', '1', '2023-03-03 9:30:00','14.88','3.30'),
    (108, 1003, 'Large', 'Original', '1', '2023-03-03 9:30:00','14.88','3.30'),
    (109, 1003, 'Large', 'Original', '1', '2023-03-03 9:30:00','14.88','3.30'),
    (110, 1004, 'XLarge', 'Original', '1', '2023-04-20 7:11:00','27.94','9.19'),
    (111, 1004, 'XLarge', 'Original', '1', '2023-04-20 7:11:00', '31.50','6.25'),
    (112, 1004, 'XLarge', 'Original', '1', '2023-04-20 7:11:00', '26.75', '8.18'),
    (113, 1005, 'XLarge', 'Gluten-Free', '1', '2023-03-02 5:30:00', '27.45', '7.88'),
    (114, 1006, 'Large', 'Thin', '1', '2023-03-02 6:17:00', '25.81','4.24'),
    (115, 1007, 'Large', 'Thin', '1', '2023-04-13 8:32:00', '18.00','2.75'),
    (116, 1007, 'Large', 'Thin', '1', '2023-04-13 8:32:00', '19.25','3.25');

INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '101', DiscountID FROM discount
WHERE DiscountID = '102';
INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '102', DiscountID FROM discount
WHERE DiscountID = '101';
INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '102', DiscountID FROM discount
WHERE DiscountID = '103';
INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '110', DiscountID FROM discount
WHERE DiscountID = '105';
INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '111', DiscountID FROM discount
WHERE DiscountID = '103';
INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '113', DiscountID FROM discount
WHERE DiscountID = '103';
INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '115', DiscountID FROM discount
WHERE DiscountID = '100';
INSERT INTO pizzadiscount (PizzaOrderID, DiscountID)
SELECT '116', DiscountID FROM discount
WHERE DiscountID = '100';

-- For PizzaOrderID '101'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '101', ToppingID, 1 FROM topping
WHERE ToppingID IN ('113', '101', '102'); -- Regular Cheese, Pepperoni, Sausage

-- For PizzaOrderID '102'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '102', ToppingID, 0 FROM topping
WHERE ToppingID IN ('115', '109', '107', '108', '112'); -- Feta Cheese, Black Olives, Roma Tomato, Mushrooms, Banana Peppers

-- For PizzaOrderID '103'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '103', ToppingID, 0 FROM topping
WHERE ToppingID IN ('113', '104', '112'); -- Regular Cheese, Chicken, Banana Peppers

-- For PizzaOrderID '104' to '109'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '104', ToppingID, 0 FROM topping
WHERE ToppingID IN ('113', '101'); -- Regular Cheese, Pepperoni

-- Repeat the above statement for PizzaOrderID '105' to '109'

-- For PizzaOrderID '110'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '110', ToppingID, 0 FROM topping
WHERE ToppingID IN ('114', '101', '102'); -- Four Cheese Blend, Pepperoni, Sausage

-- For PizzaOrderID '111'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '111', ToppingID, 1 FROM topping
WHERE ToppingID IN ('114', '103', '110'); -- Four Cheese Blend, Ham, Pineapple

-- For PizzaOrderID '112'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '112', ToppingID, 0 FROM topping
WHERE ToppingID IN ('114', '104', '117'); -- Four Cheese Blend, Chicken, Bacon

-- For PizzaOrderID '113'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '113', ToppingID, 0 FROM topping
WHERE ToppingID IN ('116', '105', '106', '107', '108', '109'); -- Goat Cheese, Green Pepper, Onion, Roma Tomato, Mushrooms, Black Olives

-- For PizzaOrderID '114'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '114', ToppingID, 1 FROM topping
WHERE ToppingID IN ('114', '104', '105', '106', '108'); -- Four Cheese Blend, Chicken, Green Peppers, Onion, Mushrooms

-- For PizzaOrderID '115'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '115', ToppingID, 1 FROM topping
WHERE ToppingID = '114'; -- Four Cheese Blend

-- For PizzaOrderID '116'
INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping)
SELECT '116', ToppingID, 1 FROM topping
WHERE ToppingID IN ('113', '101'); -- Regular Cheese, Pepperoni
