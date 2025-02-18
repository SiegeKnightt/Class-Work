USE Pizzeria;

CREATE VIEW ToppingPopularity AS
SELECT t.ToppingName AS Topping, 
       COUNT(t.ToppingSmallUnits + t.ToppingMediumUnits + t.ToppingLargeUnits + t.ToppingXLargeUnits) + ot.ExtraTopping +  
       CASE WHEN t.ToppingName = 'Four Cheese Blend' THEN 2 ELSE 0 END AS ToppingCount
FROM topping t
JOIN ordertopping ot ON t.ToppingID = ot.ToppingID
GROUP BY t.ToppingName
ORDER BY ToppingCount DESC, ToppingName;

CREATE VIEW ProfitByPizza AS
SELECT bp.BasePizzaSize AS Size, 
       bp.BasePizzaCrust AS Crust, 
       ROUND(SUM(po.PizzaOrderPrice - po.PizzaOrderCost), 2) AS Profit,
       DATE_FORMAT(po.PizzaOrderTime, '%c/%Y') AS OrderMonth
FROM basepizza bp
JOIN pizzaorder po ON bp.BasePizzaSize = po.PizzaOrderPizzaSize AND bp.BasePizzaCrust = po.PizzaOrderPizzaCrust
GROUP BY bp.BasePizzaSize, bp.BasePizzaCrust
ORDER BY Profit DESC;

CREATE VIEW ProfitByOrderType AS
SELECT
  op.OrderType AS customerType,
  DATE_FORMAT(op.OrderTimeStamp, '%c/%Y') AS OrderMonth,
  SUM(po.PizzaOrderPrice) AS TotalOrderPrice,
  ROUND(SUM(po.PizzaOrderCost), 2) AS TotalOrderCost,
  ROUND(SUM(po.PizzaOrderPrice - po.PizzaOrderCost), 2) AS Profit
FROM orderpizza op  
JOIN pizzaorder po ON op.OrderID = po.PizzaOrderOrderID
GROUP BY op.OrderType, OrderMonth
UNION ALL
SELECT
  NULL AS customerType,
  'Grand Total' AS OrderMonth,
  SUM(po.PizzaOrderPrice) AS TotalOrderPrice,
  ROUND(SUM(po.PizzaOrderCost), 2) AS TotalOrderCost,
  ROUND(SUM(po.PizzaOrderPrice - po.PizzaOrderCost), 2) AS Profit
FROM orderpizza op  
JOIN pizzaorder po ON op.OrderID = po.PizzaOrderOrderID

ORDER BY 
  CASE 
	WHEN customerType = 'Dinein' THEN 1 
	WHEN customerType = 'Pickup' THEN 2
	WHEN customerType = 'Delivery' THEN 3
    ELSE 4
  END, 
  TotalOrderPrice DESC;

SELECT * FROM ToppingPopularity;
SELECT * FROM ProfitByPizza;
SELECT * FROM ProfitByOrderType;