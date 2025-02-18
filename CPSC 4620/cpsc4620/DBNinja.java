package cpsc4620;

import java.io.IOException;
import java.sql.*;
import java.util.*;
import java.util.Date;

/*
 * This file is where most of your code changes will occur You will write the code to retrieve
 * information from the database, or save information to the database
 * 
 * The class has several hard coded static variables used for the connection, you will need to
 * change those to your connection information
 * 
 * This class also has static string variables for pickup, delivery and dine-in. If your database
 * stores the strings differently (i.e "pick-up" vs "pickup") changing these static variables will
 * ensure that the comparison is checking for the right string in other places in the program. You
 * will also need to use these strings if you store this as boolean fields or an integer.
 * 
 * 
 */

/**
 * A utility class to help add and retrieve information from the database
 */

public final class DBNinja {
	private static Connection conn;

	// Change these variables to however you record dine-in, pick-up and delivery, and sizes and crusts
	public final static String pickup = "pickup";
	public final static String delivery = "delivery";
	public final static String dine_in = "dinein";

	public final static String size_s = "Small";
	public final static String size_m = "Medium";
	public final static String size_l = "Large";
	public final static String size_xl = "XLarge";

	public final static String crust_thin = "Thin";
	public final static String crust_orig = "Original";
	public final static String crust_pan = "Pan";
	public final static String crust_gf = "Gluten-Free";



	
	private static boolean connect_to_db() throws SQLException, IOException {

		try {
			conn = DBConnector.make_connection();
			return true;
		} catch (SQLException e) {
			return false;
		} catch (IOException e) {
			return false;
		}

	}

	
	public static void addOrder(Order o) throws SQLException, IOException
	{
		connect_to_db();
		/*
		 * add code to add the order to the DB. Remember that we're not just
		 * adding the order to the order DB table, but we're also recording
		 * the necessary data for the delivery, dinein, and pickup tables
		 * 
		 */

		PreparedStatement statement = conn.prepareStatement("insert into orderpizza (OrderID, OrderCost, OrderType, OrderTimeStamp, OrderState, OrderPrice, OrderCustID) values (?, ?, ?, ?, ?, ?, ?)");

		statement.setInt(1, o.getOrderID());
		statement.setDouble(2, o.getBusPrice());
		statement.setString(3, o.getOrderType());
		statement.setString(4, o.getDate());
		statement.setInt(5, o.getIsComplete());
		statement.setDouble(6, o.getCustPrice());
		statement.setInt(7, o.getCustID());

		statement.executeUpdate();

		if (o instanceof DineinOrder) {

			DineinOrder d = (DineinOrder) o;

			PreparedStatement s = conn.prepareStatement("insert into dinein (OrderID, OrderCost, OrderType, OrderTimeStamp, OrderState, OrderPrice, OrderCustID, TableNum) values (?, ?, ?, ?, ?, ?, ?, ?)");

			s.setInt(1, d.getOrderID());
			s.setDouble(2, d.getBusPrice());
			s.setString(3, d.getOrderType());
			s.setString(4, d.getDate());
			s.setInt(5, d.getIsComplete());
			s.setDouble(6, d.getCustPrice());
			s.setInt(7, d.getCustID());
			s.setInt(8, d.getTableNum());

			s.executeUpdate();
			s.close();
		}
		else if (o instanceof PickupOrder) {

			PickupOrder p = (PickupOrder) o;

			PreparedStatement s = conn.prepareStatement("insert into pickup (OrderID, OrderCost, OrderType, OrderTimeStamp, OrderState, OrderPrice, OrderCustID) values (?, ?, ?, ?, ?, ?, ?)");

			s.setInt(1, p.getOrderID());
			s.setDouble(2, p.getBusPrice());
			s.setString(3, p.getOrderType());
			s.setString(4, p.getDate());
			s.setInt(5, p.getIsComplete());
			s.setDouble(6, p.getCustPrice());
			s.setInt(7, p.getCustID());

			s.executeUpdate();
			s.close();
		}
		else if (o instanceof DeliveryOrder) {

			DeliveryOrder d = (DeliveryOrder) o;

			PreparedStatement s = conn.prepareStatement("insert into pickup (OrderID, OrderCost, OrderType, OrderTimeStamp, OrderState, OrderPrice, OrderCustID, CustAddress) values (?, ?, ?, ?, ?, ?, ?, ?)");

			s.setInt(1, d.getOrderID());
			s.setDouble(2, d.getBusPrice());
			s.setString(3, d.getOrderType());
			s.setString(4, d.getDate());
			s.setInt(5, d.getIsComplete());
			s.setDouble(6, d.getCustPrice());
			s.setInt(7, d.getCustID());
			s.setString(8, d.getAddress());

			s.executeUpdate();
			s.close();
		}

		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();
	}
	
	public static void addPizza(Pizza p) throws SQLException, IOException
	{
		connect_to_db();
		/*
		 * Add the code needed to insert the pizza into into the database.
		 * Keep in mind adding pizza discounts and toppings associated with the pizza,
		 * there are other methods below that may help with that process.
		 * 
		 */

		// Insert the pizza into the pizzaorder table
		String sql = "INSERT INTO pizzaorder (PizzaOrderID, PizzaOrderOrderID, PizzaOrderPizzaSize, PizzaOrderPizzaCrust, PizzaOrderPizzaState, PizzaOrderTime, PizzaOrderPrice, PizzaOrderCost) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
		PreparedStatement pstmt = conn.prepareStatement(sql);

		// Set parameters for the INSERT statement based on the Pizza object
		pstmt.setInt(1, p.getPizzaID());
		pstmt.setInt(2, p.getOrderID());
		pstmt.setString(3, p.getSize());
		pstmt.setString(4, p.getCrustType());
		pstmt.setString(5, p.getPizzaState());
		pstmt.setString(6, p.getPizzaDate());
		pstmt.setDouble(7, p.getCustPrice());
		pstmt.setDouble(8, p.getBusPrice());

		// Execute the INSERT statement
		pstmt.executeUpdate();
		pstmt.close();

		for (Topping t : p.getToppings()) {

			if (p.getIsDoubleArray()[t.getTopID()]) {

				useTopping(p, t, true);
			}
			else {

				useTopping(p, t, false);
			}
		}
	}
	
	
	public static void useTopping(Pizza p, Topping t, boolean isDoubled) throws SQLException, IOException //this method will update toppings inventory in SQL and add entities to the Pizzatops table. Pass in the p pizza that is using t topping
	{
		connect_to_db();
		/*
		 * This method should do 2 two things.
		 * - update the topping inventory every time we use t topping (accounting for extra toppings as well)
		 * - connect the topping to the pizza
		 *   What that means will be specific to your yimplementatinon.
		 * 
		 * Ideally, you should't let toppings go negative....but this should be dealt with BEFORE calling this method.
		 * 
		 */

		String updateInventorySql = "UPDATE topping SET ToppingInventory = ToppingInventory - ? WHERE ToppingID = ?";
		PreparedStatement update = conn.prepareStatement(updateInventorySql);

		// If the topping is doubled, we use twice as much
		int amountNeeded = isDoubled ? 2 : 1;
		update.setInt(1, amountNeeded);
		update.setInt(2, t.getTopID());

		update.executeUpdate();
		update.close();

		// Connect the topping to the pizza
		String connectToppingSql = "INSERT INTO ordertopping (PizzaOrderID, ToppingID, ExtraTopping) VALUES (?, ?, ?)";
		PreparedStatement connect = conn.prepareStatement(connectToppingSql);

		connect.setInt(1, p.getPizzaID());
		connect.setInt(2, t.getTopID());
		connect.setBoolean(3, isDoubled);

		connect.executeUpdate();
		connect.close();
	}
	
	
	public static void usePizzaDiscount(Pizza p, Discount d) throws SQLException, IOException
	{
		connect_to_db();
		/*
		 * This method connects a discount with a Pizza in the database.
		 * 
		 * What that means will be specific to your implementatinon.
		 */

		String connectDiscount = "INSERT INTO pizzadiscount (PizzaOrderID, DiscountID) values (?, ?) where PizzaOrderID = ?";
		PreparedStatement connect = conn.prepareStatement(connectDiscount);

		connect.setInt(1, p.getPizzaID());
		connect.setInt(2, d.getDiscountID());
		
		connect.executeUpdate();
		connect.close();
	}
	
	public static void useOrderDiscount(Order o, Discount d) throws SQLException, IOException
	{
		connect_to_db();
		/*
		 * This method connects a discount with an order in the database
		 * 
		 * You might use this, you might not depending on where / how to want to update
		 * this information in the dabast
		 */

		String connectDiscount = "insert into orderdiscount (OrderID, DiscountID) values (?, ?) where PizzaOrderID = ?";
		PreparedStatement connect = conn.prepareStatement(connectDiscount);

		connect.setInt(1, o.getOrderID());
		connect.setInt(2, d.getDiscountID());

		connect.executeUpdate();
		connect.close();
	}
	
	public static void addCustomer(Customer c) throws SQLException, IOException {
		connect_to_db();
		/*
		 * This method adds a new customer to the database.
		 * 
		 */

		String sql = "INSERT INTO customer (CustomerID, CustomerFName, CustomerLName, CustomerPhone) VALUES ( ?, ?, ?, ?)";
		PreparedStatement pstmt = conn.prepareStatement(sql);

		// Set parameters for the INSERT statement based on the Customer object;
		pstmt.setInt(1, c.getCustID());
		pstmt.setString(2, c.getFName());
		pstmt.setString(3, c.getLName());
		pstmt.setString(4, c.getPhone());

		// Execute the INSERT statement
		pstmt.executeUpdate();
		pstmt.close();
	}

	public static void completeOrder(Order o) throws SQLException, IOException {
		connect_to_db();
		/*
		 * Find the specifed order in the database and mark that order as complete in the database.
		 * 
		 */

		ArrayList<Order> orders = DBNinja.getOrders(false);

		for (Order order : orders) {

			if (order.getOrderID() == o.getOrderID()) {

				PreparedStatement statement = conn.prepareStatement("update orderpizza set OrderState = 1 where OrderID = ?");
				statement.setInt(1, o.getOrderID());

				statement.close();
				conn.close();
			}
		}
	}


	public static ArrayList<Order> getOrders(boolean openOnly) throws SQLException, IOException {
		connect_to_db();
		/*
		 * Return an arraylist of all of the orders.
		 * 	openOnly == true => only return a list of open (ie orders that have not been marked as completed)
		 *           == false => return a list of all the orders in the database
		 * Remember that in Java, we account for supertypes and subtypes
		 * which means that when we create an arrayList of orders, that really
		 * means we have an arrayList of dineinOrders, deliveryOrders, and pickupOrders.
		 * 
		 * Don't forget to order the data coming from the database appropriately.
		 * 
		 */

		ArrayList<Order> result = new ArrayList<>();

		Statement statement = conn.createStatement();

		if (openOnly == true) {

			ResultSet resultSet = statement.executeQuery("select * from orderpizza where OrderState = 0 order by OrderID ASC");

			while (resultSet.next()) {

				Order order = new Order(
						resultSet.getInt("OrderID"),
						resultSet.getInt("OrderCustID"),
						resultSet.getString("OrderType"),
						resultSet.getString("OrderTimeStamp"),
						resultSet.getDouble("OrderPrice"),
						resultSet.getDouble("OrderCost"),
						resultSet.getInt("OrderState")
				);

				result.add(order);
			}
		}
		else if (openOnly == false) {

			ResultSet resultSet = statement.executeQuery("select * from orderpizza order by OrderID ASC");

			while (resultSet.next()) {

				Order order = new Order(
						resultSet.getInt("OrderID"),
						resultSet.getInt("OrderCustID"),
						resultSet.getString("OrderType"),
						resultSet.getString("OrderTimeStamp"),
						resultSet.getDouble("OrderPrice"),
						resultSet.getDouble("OrderCost"),
						resultSet.getInt("OrderState")
				);

				result.add(order);
			}
		}

		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();

		return result;
	}

	// Ask about throws
	public static Order getLastOrder() throws SQLException, IOException{

		/*
		 * Query the database for the LAST order added
		 * then return an Order object for that order.
		 * NOTE...there should ALWAYS be a "last order"!
		 */

		ArrayList<Order> orders = DBNinja.getOrders(false);

		int maxYear = 0;
		int maxMonth = 0;
		int maxDay = 0;

		Order latestOrder = new Order(-1, -1, "", "", -1.00, -1.00, 0);

		for (Order order : orders) {

			if (getYear(order.getDate()) > maxYear) {

				if (getMonth(order.getDate()) > maxMonth) {

					if (getDay(order.getDate()) > maxDay) {

						maxYear = getYear(order.getDate());
						maxMonth = getMonth(order.getDate());
						maxDay = getDay(order.getDate());
						latestOrder = order;
					}
				}
			}
		}

		return latestOrder;
	}

	// Ask about throws
	public static ArrayList<Order> getOrdersByDate(String date) throws SQLException, IOException {

		/*
		 * Query the database for ALL the orders placed on a specific date
		 * and return a list of those orders.
		 *  
		 */

		ArrayList<Order> orders = DBNinja.getOrders(false);
		ArrayList<Order> specific = new ArrayList<>();

		for (Order order : orders) {

			if (order.getDate().equals(date)) {

				specific.add(order);
			}
		}

		 return specific;
	}
		
	public static ArrayList<Discount> getDiscountList() throws SQLException, IOException {
		connect_to_db();
		/* 
		 * Query the database for all the available discounts and 
		 * return them in an arrayList of discounts.
		 * 
		*/
		ArrayList<Discount> result = new ArrayList<>();

		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("SELECT * FROM DISCOUNT");

		while (resultSet.next()) {
			Discount discount = new Discount(
					resultSet.getInt("DiscountID"),
					resultSet.getString("DiscountName"),
					resultSet.getDouble("DiscountAmount"),
					resultSet.getBoolean("DiscountType")
			);
			result.add(discount);
		}
		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();

		return result;
	}

	//ask about throws
	public static Discount findDiscountByName(String name) throws SQLException, IOException {
		/*
		 * Query the database for a discount using it's name.
		 * If found, then return an OrderDiscount object for the discount.
		 * If it's not found....then return null
		 *  
		 */

		ArrayList<Discount> discounts = DBNinja.getDiscountList();

		for (Discount discount : discounts) {

			if (discount.getDiscountName().equals(name)) {

				return discount;
			}
		}

		 return null;
	}


	public static ArrayList<Customer> getCustomerList() throws SQLException, IOException {
		connect_to_db();
		/*
		 * Query the data for all the customers and return an arrayList of all the customers. 
		 * Don't forget to order the data coming from the database appropriately.
		 * 
		*/

		ArrayList<Customer> result = new ArrayList<>();

		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("select * from customer order by CustomerLName, CustomerFName, CustomerPhone");

		while (resultSet.next()) {

			Customer customer = new Customer(
					resultSet.getInt("CustomerID"),
					resultSet.getString("CustomerFName"),
					resultSet.getString("CustomerLName"),
					resultSet.getString("CustomerPhone")
			);

			customer.setAddress(
					resultSet.getString("CustomerStreet"),
					resultSet.getString("CustomerCity"),
					resultSet.getString("CustomerState"),
					resultSet.getString("CustomerZip")
			);

			result.add(customer);
		}

		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();

		return result;
	}

	// Ask about throws
	public static Customer findCustomerByPhone(String phoneNumber) throws SQLException, IOException {
		/*
		 * Query the database for a customer using a phone number.
		 * If found, then return a Customer object for the customer.
		 * If it's not found....then return null
		 *  
		 */
		
		ArrayList<Customer> customers = DBNinja.getCustomerList();

		for (Customer customer : customers) {

			if (customer.getPhone().equals(phoneNumber)) {

				return customer;
			}
		}

		 return null;
	}


	public static ArrayList<Topping> getToppingList() throws SQLException, IOException {
		connect_to_db();
		/*
		 * Query the database for the aviable toppings and 
		 * return an arrayList of all the available toppings. 
		 * Don't forget to order the data coming from the database appropriately.
		 * 
		 */


		ArrayList<Topping> result = new ArrayList<>();

		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("select * from topping order by ToppingID asc");

		while (resultSet.next()) {

			Topping topping = new Topping(
					resultSet.getInt("ToppingID"),
					resultSet.getString("ToppingName"),
					resultSet.getDouble("ToppingSmallUnits"),
					resultSet.getDouble("ToppingMediumUnits"),
					resultSet.getDouble("ToppingLargeUnits"),
					resultSet.getDouble("ToppingXLargeUnits"),
					resultSet.getDouble("ToppingPricePerUnit"),
					resultSet.getDouble("ToppingCostPerUnit"),
					resultSet.getInt("ToppingMinimum"),
					resultSet.getInt("ToppingInventory")
			);

			result.add(topping);
		}

		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();
		
		return result;
	}

	// Ask about throws
	public static Topping findToppingByName(String name) throws SQLException, IOException {
		/*
		 * Query the database for the topping using it's name.
		 * If found, then return a Topping object for the topping.
		 * If it's not found....then return null
		 *  
		 */

		ArrayList<Topping> toppings = DBNinja.getToppingList();

		for (Topping topping : toppings) {

			if (topping.getTopName().equals(name)) {

				return topping;
			}
		}

		 return null;
	}


	public static void addToInventory(Topping t, double quantity) throws SQLException, IOException {
		connect_to_db();
		/*
		 * Updates the quantity of the topping in the database by the amount specified.
		 * 
		 * */

		String addInventory = "UPDATE topping SET ToppingInventory = ToppingInventory + ? WHERE ToppingName = ?";
		PreparedStatement addState = conn.prepareStatement(addInventory);

		addState.setDouble(1, quantity);
		addState.setString(2, t.getTopName());
		
		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		addState.executeUpdate();
		addState.close();
	}
	
	public static double getBaseCustPrice(String size, String crust) throws SQLException, IOException {
		connect_to_db();
		/* 
		 * Query the database for the base customer price for that size and crust pizza.
		 * 
		*/

		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("select * from pizzaorder");

		double result = 0.0;

		while (resultSet.next()) {

			if (resultSet.getString("PizzaOrderPizzaSize").equals(size) && resultSet.getString("PizzaOrderPizzaCrust").equals(crust)) {

				result =  resultSet.getDouble("PizzaOrderPrice");
			}

		}
		
		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();

		return result;
	}

	public static double getBaseBusPrice(String size, String crust) throws SQLException, IOException {
		connect_to_db();
		/* 
		 * Query the database for the base business price for that size and crust pizza.
		 * 
		*/

		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("select * from pizzaorder");

		double result = 0.0;

		while (resultSet.next()) {

			if (resultSet.getString("PizzaOrderPizzaSize").equals(size) && resultSet.getString("PizzaOrderPizzaCrust").equals(crust)) {

				result = resultSet.getDouble("PizzaOrderCost");
			}

		}

		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();

		return result;
	}

	public static void printInventory() throws SQLException, IOException {
		connect_to_db();
		/*
		 * Queries the database and prints the current topping list with quantities.
		 *  
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 */


		ArrayList<Topping> toppings = DBNinja.getToppingList();

		for (Topping topping : toppings) {

			System.out.print(topping.getTopID());
			System.out.print(" " + topping.getTopName());
			System.out.println(" " + topping.getCurINVT());
		}
	}
	
	public static void printToppingPopReport() throws SQLException, IOException
	{
		connect_to_db();
		/*
		 * Prints the ToppingPopularity view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 */

		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("select * from ToppingPopularity");

		System.out.println("Topping\tToppingCount");
		while (resultSet.next()) {

			System.out.println(resultSet.getString("Topping") + "\t" + resultSet.getInt("ToppingCount"));
		}
		
		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();
	}
	
	public static void printProfitByPizzaReport() throws SQLException, IOException
	{
		connect_to_db();
		/*
		 * Prints the ProfitByPizza view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 */


		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("select * from ProfitByPizza");

		System.out.println("Size\tCrust\tProfit\tOrderMonth");

		while (resultSet.next()) {

			System.out.println(resultSet.getString("Size") + "\t" + resultSet.getString("Crust") + "\t" + resultSet.getDouble("Profit") + "\t" + resultSet.getString("OrderMonth"));
		}

		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();
	}
	
	public static void printProfitByOrderType() throws SQLException, IOException
	{
		connect_to_db();
		/*
		 * Prints the ProfitByOrderType view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 */

		Statement statement = conn.createStatement();

		ResultSet resultSet = statement.executeQuery("select * from ProfitByOrderType");

		System.out.println("CustomerType\tOrderMonth\tTotalOrderPrice\tTotalOrderCost\tProfit");

		while (resultSet.next()) {

			System.out.println(resultSet.getString("customerType") + "\t" + resultSet.getString("OrderMonth") + "\t" + resultSet.getDouble("TotalOrderPrice") + "\t" + resultSet.getDouble("TotalOrderCost") + "\t" + resultSet.getDouble("Profit"));
		}

		//DO NOT FORGET TO CLOSE YOUR CONNECTION
		statement.close();
		conn.close();
	}
	
	
	
	public static String getCustomerName(int CustID) throws SQLException, IOException
	{
	/*
		 * This is a helper method to fetch and format the name of a customer
		 * based on a customer ID. This is an example of how to interact with 
		 * your database from Java.  It's used in the model solution for this project...so the code works!
		 * 
		 * OF COURSE....this code would only work in your application if the table & field names match!
		 *
		 */

		 connect_to_db();

		/* 
		* an example of the same query using a prepared statement...
		* 
		*/
		String cname1 = "";
		PreparedStatement os;
		ResultSet rset2;
		String query2;
		query2 = "Select CustomerFName, CustomerLName From customer WHERE CustomerID=?;";
		os = conn.prepareStatement(query2);
		os.setInt(1, CustID);
		rset2 = os.executeQuery();
		while(rset2.next())
		{
			cname1 = rset2.getString("CustomerFName") + " " + rset2.getString("CustomerLName"); // note the use of field names in the getSting methods
		}

		conn.close();
		return cname1; // OR cname2
	}

	/*
	 * The next 3 private methods help get the individual components of a SQL datetime object. 
	 * You're welcome to keep them or remove them.
	 */
	public static int getYear(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(0,4));
	}
	public static int getMonth(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(5, 7));
	}
	public static int getDay(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(8, 10));
	}

	public static boolean checkDate(int year, int month, int day, String dateOfOrder)
	{
		if(getYear(dateOfOrder) > year)
			return true;
		else if(getYear(dateOfOrder) < year)
			return false;
		else
		{
			if(getMonth(dateOfOrder) > month)
				return true;
			else if(getMonth(dateOfOrder) < month)
				return false;
			else
			{
				if(getDay(dateOfOrder) >= day)
					return true;
				else
					return false;
			}
		}
	}


}