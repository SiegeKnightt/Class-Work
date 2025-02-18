package cpsc4620;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/*
 * This file is where the front end magic happens.
 *
 * You will have to write the methods for each of the menu options.
 *
 * This file should not need to access your DB at all, it should make calls to the DBNinja that will do all the connections.
 *
 * You can add and remove methods as you see necessary. But you MUST have all of the menu methods (including exit!)
 *
 * Simply removing menu methods because you don't know how to implement it will result in a major error penalty (akin to your program crashing)
 *
 * Speaking of crashing. Your program shouldn't do it. Use exceptions, or if statements, or whatever it is you need to do to keep your program from breaking.
 *
 */

public class Menu {

	public static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws SQLException, IOException {

		System.out.println("Welcome to Pizzas-R-Us!");

		int menu_option = 0;

		// present a menu of options and take their selection

		PrintMenu();
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String option = reader.readLine();
		menu_option = Integer.parseInt(option);

		while (menu_option != 9) {
			switch (menu_option) {
				case 1:// enter order
					EnterOrder();
					break;
				case 2:// view customers
					viewCustomers();
					break;
				case 3:// enter customer
					EnterCustomer();
					break;
				case 4:// view order
					// open/closed/date
					ViewOrders();
					break;
				case 5:// mark order as complete
					MarkOrderAsComplete();
					break;
				case 6:// view inventory levels
					ViewInventoryLevels();
					break;
				case 7:// add to inventory
					AddInventory();
					break;
				case 8:// view reports
					PrintReports();
					break;
			}
			PrintMenu();
			option = reader.readLine();
			menu_option = Integer.parseInt(option);
		}

	}

	// allow for a new order to be placed
	public static void EnterOrder() throws SQLException, IOException {

		/*
		 * EnterOrder should do the following:
		 *
		 * Ask if the order is delivery, pickup, or dinein
		 *   if dine in....ask for table number
		 *   if pickup...
		 *   if delivery...
		 *
		 * Then, build the pizza(s) for the order (there's a method for this)
		 *  until there are no more pizzas for the order
		 *  add the pizzas to the order
		 *
		 * Apply order discounts as needed (including to the DB)
		 *
		 * return to menu
		 *
		 * make sure you use the prompts below in the correct order!
		 */

		BufferedReader read = new BufferedReader(new InputStreamReader(System.in));

		Order order = new Order(-1, -1, "", "", -1.00, -1.00, 0);
		Customer customer = new Customer(-1, "", "", "");

		// User Input Prompts...
		System.out.println("Is this order for: \n1.) Dine-in\n2.) Pick-up\n3.) Delivery\nEnter the number of your choice:");
		int choice = Integer.parseInt(read.readLine());
		switch (choice) {
			case 1:
				order.setOrderType("dinein");
				// Need to add functionality
				System.out.println("What is the table number for this order?");
				int table = Integer.parseInt(read.readLine());
				DineinOrder o;
				//o.setTableNum(table);
				break;
			case 2:
				order.setOrderType("pickup");
				System.out.println("Is this order for an existing customer? Answer y/n: ");
				String choice2 = read.readLine();

				while (!choice2.equals("y") && !choice2.equals("n")) {

					System.out.println("ERROR: I don't understand your input for: Is this order an existing customer?");
					choice2 = read.readLine();
				}

				switch (choice2) {
					case "y":
						System.out.println("Here's a list of the current customers: ");
						viewCustomers();
						System.out.println("Which customer is this order for? Enter ID Number:");
						int choice3 = Integer.parseInt(read.readLine());
						order.setCustID(choice3);
					case "n":
						// Logic to get a CustID for new customer
						List<Customer> customers = DBNinja.getCustomerList();
						int max = 0;
						for (Customer cust : customers) {

							if (cust.getCustID() > max) {

								max = cust.getCustID();
							}
						}
						max++;
						order.setCustID(max);
						customer.setCustID(max);
						System.out.println("Please enter the customer's first name:");
						String fname = read.readLine();
						customer.setFName(fname);
						System.out.println("Please enter the customer's last name:");
						String lname = read.readLine();
						customer.setLName(lname);
						System.out.println("Please enter the customer's phone number:");
						String phone = read.readLine();
						customer.setPhone(phone);
				}
				break;
			case 3:
				order.setOrderType("delivery");
				System.out.println("Is this order for an existing customer? Answer y/n: ");
				choice2 = read.readLine();

				while (!choice2.equals("y") && !choice2.equals("n")) {

					System.out.println("ERROR: I don't understand your input for: Is this order an existing customer?");
					choice2 = read.readLine();
				}

				switch (choice2) {
					case "y":
						System.out.println("Here's a list of the current customers: ");
						viewCustomers();
						System.out.println("Which customer is this order for? Enter ID Number:");
						int choice3 = Integer.parseInt(read.readLine());
						order.setCustID(choice3);
					case "n":
						// Logic to get a CustID for new customer
						List<Customer> customers = DBNinja.getCustomerList();
						int max = 0;
						for (Customer cust : customers) {

							if (cust.getCustID() > max) {

								max = cust.getCustID();
							}
						}
						max++;
						order.setCustID(max);
						customer.setCustID(max);
						System.out.println("Please enter the customer's first name:");
						String fname = read.readLine();
						customer.setFName(fname);
						System.out.println("Please enter the customer's last name:");
						String lname = read.readLine();
						customer.setLName(lname);
						System.out.println("Please enter the customer's phone number:");
						String phone = read.readLine();
						customer.setPhone(phone);
				}

				System.out.println("What is the House/Apt Number for this order? (e.g., 111)");
				int num = Integer.parseInt(read.readLine());
				System.out.println("What is the Street for this order? (e.g., Smile Street)");
				String s = read.readLine();
				String street = num + " " + s;
				System.out.println("What is the City for this order? (e.g., Greenville)");
				String city = read.readLine();
				System.out.println("What is the State for this order? (e.g., SC)");
				String state = read.readLine();
				System.out.println("What is the Zip Code for this order? (e.g., 20605)");
				String zip = read.readLine();
				customer.setAddress(street, city, state, zip);
				break;
		}
		System.out.println("Let's build a pizza!");
		int buildFlag = 0;
		while(buildFlag != -1){
			order.setOrderID(order.getOrderID() + 1);
			int num = order.getOrderID();
			buildPizza(num);
			System.out.println("Enter -1 to stop adding pizzas...Enter anything else to continue adding pizzas to the order.");
			buildFlag = Integer.parseInt(read.readLine());
		}

		System.out.println("Do you want to add discounts to this order? Enter y/n?");
		int buildFlag2 = 0;
		while(buildFlag2 != -1){
			for (Discount discount : order.getDiscountList()) {

				System.out.println(discount.toString());
			}
			System.out.println("Which Order Discount do you want to add? Enter the DiscountID. Enter -1 to stop adding Discounts: ");
			buildFlag2 = Integer.parseInt(read.readLine());
			for (Discount discount : order.getDiscountList()) {

				if (discount.getDiscountID() == buildFlag2) {

					DBNinja.useOrderDiscount(order, discount);
				}
			}
		}

		DBNinja.addCustomer(customer);
		DBNinja.addOrder(order);

		System.out.println("Finished adding order...Returning to menu...");
	}


	public static void viewCustomers() throws SQLException, IOException {
		/*
		 * Simply print out all of the customers from the database.
		 */

		List<Customer> customers = DBNinja.getCustomerList();

		for (Customer customer : customers) {

			System.out.println(customer.toString());
		}
	}


	// Enter a new customer in the database
	public static void EnterCustomer() throws SQLException, IOException {
		/*
		 * Ask for the name of the customer:
		 *   First Name <space> Last Name
		 *
		 * Ask for the  phone number.
		 *   (##########) (No dash/space)
		 *
		 * Once you get the name and phone number, add it to the DB
		 */

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

		// User Input Prompts...
		System.out.println("What is this customer's name (first <space> last)");
		String name = reader.readLine();
		System.out.println("What is this customer's phone number (##########) (No dash/space)");
		String phone = reader.readLine();

		List<Customer> customers = DBNinja.getCustomerList();
		int max = 0;
		for (Customer customer : customers) {

			if (customer.getCustID() > max) {

				max = customer.getCustID();
			}
		}
		max++;

		String[] names = name.split(" ");

		Customer customer = new Customer(max, names[0], names[1], phone);

		DBNinja.addCustomer(customer);
	}

	// View any orders that are not marked as completed
	public static void ViewOrders() throws SQLException, IOException {
		/*
		 * This method allows the user to select between three different views of the Order history:
		 * The program must display:
		 * a.	all open orders
		 * b.	all completed orders
		 * c.	all the orders (open and completed) since a specific date (inclusive)
		 *
		 * After displaying the list of orders (in a condensed format) must allow the user to select a specific order for viewing its details.
		 * The details include the full order type information, the pizza information (including pizza discounts), and the order discounts.
		 *
		 */
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));


		// User Input Prompts...
		System.out.println("Would you like to:\n(a) display all orders [open or closed]\n(b) display all open orders\n(c) display all completed [closed] orders\n(d) display orders since a specific date");
		String choice = reader.readLine();
		switch (choice) {
			case "a":
				ArrayList<Order> o = DBNinja.getOrders(false);
				for (Order order : o) {

					if (order.getIsComplete() == 1 || order.getIsComplete() == 0) {

						System.out.println(order.toString());
					}
				}
				break;
			case "b":
				ArrayList<Order> ord = DBNinja.getOrders(true);
				for (Order order : ord) {

					if (order.getIsComplete() == 0) {

						System.out.println(order.toString());
					}
				}
				break;
			case "c":
				ArrayList<Order> orders = DBNinja.getOrders(false);
				for (Order order : orders) {

					if (order.getIsComplete() == 1) {

						System.out.println(order.toString());
					}
				}
				break;
			case "d":
				System.out.println("What is the date you want to restrict by? (FORMAT= YYYY-MM-DD)");
				String date = reader.readLine();
				ArrayList<Order> ordersbydate = DBNinja.getOrders(false);
				int year = DBNinja.getYear(date);
				int month = DBNinja.getMonth(date);
				int day = DBNinja.getDay(date);
				for (Order order : ordersbydate) {

					String odate = order.getDate();

					if (DBNinja.checkDate(year, month, day, odate)) {

						System.out.println(order.toString());
					}
				}
				break;
			default:
				System.out.println("I don't understand that input, returning to menu");
				break;
		}
		int option = 0;

		while (option != -1) {

			System.out.println("Which order would you like to see in detail? Enter the number (-1 to exit): ");
			option = Integer.parseInt(reader.readLine());
			ArrayList<Order> orders = DBNinja.getOrders(false);
			for (Order order : orders) {

				if (option == order.getOrderID()) {

					System.out.println(order.toString());
					return;
				}
				else if (option < 0) {

					System.out.println("Incorrect entry, returning to menu.");
					return;
				}
			}
		}

		System.out.println("No orders to display, returning to menu.");
	}


	// When an order is completed, we need to make sure it is marked as complete
	public static void MarkOrderAsComplete() throws SQLException, IOException {
		/*
		 * All orders that are created through java (part 3, not the orders from part 2) should start as incomplete
		 *
		 * When this method is called, you should print all of the "opoen" orders marked
		 * and allow the user to choose which of the incomplete orders they wish to mark as complete
		 *
		 */

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

		List<Order> orders = DBNinja.getOrders(false);

		boolean openOrders = false;

		// User Input Prompts...
		for (Order order : orders) {

			if (order.getIsComplete() == 0) {

				openOrders = true;
			}
		}

		if (!openOrders) {

			System.out.println("There are no open orders currently... returning to menu...");
			return;
		}

		System.out.println("Which order would you like mark as complete? Enter the OrderID: ");
		int id = Integer.parseInt(reader.readLine());

		for (Order order : orders) {

			if (order.getOrderID() == id) {

				order.setIsComplete(1);
				return;
			}
		}

		System.out.println("Incorrect entry, not an option");
		MarkOrderAsComplete();
	}

	public static void ViewInventoryLevels() throws SQLException, IOException {
		/*
		 * Print the inventory. Display the topping ID, name, and current inventory
		 */


		List<Topping> toppings = DBNinja.getToppingList();

		for (Topping topping : toppings) {

			System.out.print("TopID= " + topping.getTopID());
			System.out.print(" ");
			System.out.print("Name= " + topping.getTopName());
			System.out.print("\t");
			System.out.println("CurINVT= " + topping.getCurINVT());
		}
	}


	public static void AddInventory() throws SQLException, IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		/*
		 * This should print the current inventory and then ask the user which topping (by ID) they want to add more to and how much to add
		 */
		ViewInventoryLevels();

		// User Input Prompts...
		System.out.println("Which topping do you want to add inventory to? Enter the number: ");
		int selectedToppingID = Integer.parseInt(reader.readLine());
		int flag = 0;
		ArrayList<Topping> toppings = DBNinja.getToppingList();
		Topping selectedTop = new Topping(-1, "", -1.00, -1.00, -1.00, -1.00, -1.00, -1.00, -1, -1);
		for (Topping topping : toppings) {

			if (topping.getTopID() == selectedToppingID) {

				selectedTop = topping;
				flag = 1;
			}
		}
		System.out.println("How many units would you like to add? ");
		int addedUnits = Integer.parseInt(reader.readLine());

		if (flag == 0) {

			System.out.println("Incorrect entry, not an option");
			return;
		}

		DBNinja.addToInventory(selectedTop, addedUnits);
	}

	// A method that builds a pizza. Used in our add new order method
	public static Pizza buildPizza(int orderID) throws SQLException, IOException {

		/*
		 * This is a helper method for first menu option.
		 *
		 * It should ask which size pizza the user wants and the crustType.
		 *
		 * Once the pizza is created, it should be added to the DB.
		 *
		 * We also need to add toppings to the pizza. (Which means we not only need to add toppings here, but also our bridge table)
		 *
		 * We then need to add pizza discounts (again, to here and to the database)
		 *
		 * Once the discounts are added, we can return the pizza
		 */

		Pizza ret = null;
		double cost = 0.0;
		double price = 0.0;
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

		// User Input Prompts...
		System.out.println("What size is the pizza?");
		System.out.println("1." + DBNinja.size_s);
		System.out.println("2." + DBNinja.size_m);
		System.out.println("3." + DBNinja.size_l);
		System.out.println("4." + DBNinja.size_xl);
		System.out.println("Enter the corresponding number: ");
		int choice = Integer.parseInt(reader.readLine());
		String size = "";
		switch (choice) {
			case 1:
				size = DBNinja.size_s;
				price = price + 3.00;
				cost = cost + 0.75;
				break;
			case 2:
				size = DBNinja.size_m;
				price = price + 5.00;
				cost = cost + 1.50;
				break;
			case 3:
				size = DBNinja.size_l;
				price = price + 8.00;
				cost = cost + 2.00;
				break;
			case 4:
				size = DBNinja.size_xl;
				price = price + 10.00;
				cost = cost + 3.00;
				break;
		}
		System.out.println("What crust for this pizza?");
		System.out.println("1." + DBNinja.crust_thin);
		System.out.println("2." + DBNinja.crust_orig);
		System.out.println("3." + DBNinja.crust_pan);
		System.out.println("4." + DBNinja.crust_gf);
		System.out.println("Enter the corresponding number: ");
		choice = Integer.parseInt(reader.readLine());
		String crust = "";
		switch (choice) {
			case 1:
				crust = DBNinja.crust_thin;
				break;
			case 2:
				crust = DBNinja.crust_orig;
				break;
			case 3:
				crust = DBNinja.crust_pan;
				break;
			case 4:
				crust = DBNinja.crust_gf;
				break;
		}

		int add = 0;
		int exAdd = 0;

		while (add != -1 && exAdd != -1) {

			System.out.println("Available Toppings:");
			ArrayList<Topping> toppings = DBNinja.getToppingList();
			for (Topping topping : toppings) {

				System.out.println(topping.toString());
			}
			ArrayList<Topping> t = DBNinja.getToppingList();
			ArrayList<Topping> answer = new ArrayList<>();
			//Topping top = new Topping(-1, "", -1.00, -1.00, -1.00, -1.00, -1.00, -1.00, -1, -1);
			System.out.println("Which topping do you want to add? Enter the TopID. Enter -1 to stop adding toppings: ");
			while (add != -1) {

				add = Integer.parseInt(reader.readLine());

				for (Topping topping : t) {

					if (topping.getTopID() == add) {
						price = price + topping.getCustPrice();
						cost = cost + topping.getBusPrice();
						topping.setCurINVT(topping.getCurINVT() - 1);
						answer.add(topping);
					}
				}
			}
			System.out.println("Do you want to add extra topping? Enter y/n");
			String extra = reader.readLine();
			if(extra.equals("y")) {

				System.out.println("Which topping do you want to add? Enter the TopID. Enter -1 to stop adding toppings: ");

				while (exAdd != -1) {

					for (Topping topping : toppings) {

						System.out.println(topping.toString());
					}

					exAdd = Integer.parseInt(reader.readLine());

					for (Topping topping : t) {

						if (topping.getTopID() == exAdd) {

							if(topping.getCurINVT() > 0) {
								price = price + topping.getCustPrice();
								cost = cost + topping.getBusPrice();
								topping.setCurINVT(topping.getCurINVT() - 1);
								answer.add(topping);
							}
							else {

								System.out.println("We don't have enough of that topping to add it...");
							}
						}
					}
				}
			}
		}

		// New while
		System.out.println("Do you want to add discounts to this Pizza? Enter y/n?");
		String addedDisc = reader.readLine();
		// Good luck adding gouda
		String glag = "y";
		if(addedDisc.equals('y')){
			while(glag.equals("n")){
				ArrayList<Discount> discounts = DBNinja.getDiscountList();
				for(Discount discount : discounts){
					System.out.println(discount.toString());
				}
				System.out.println("Which Pizza Discount do you want to add? Enter the DiscountID. Enter -1 to stop adding Discounts: ");
				int discFlag = 0;
				while(discFlag != -1){
					discFlag = Integer.parseInt(reader.readLine());

					for(Discount discount : discounts){
						if(discount.getDiscountID() == discFlag){

							if (discount.getDiscountID() == 100) {

								price = price - (price * 0.15);
							}
							else if (discount.getDiscountID() == 101) {

								price = price - 1.00;
							}
							else if (discount.getDiscountID() == 102) {

								price = price - 2.00;
							}
							else if (discount.getDiscountID() == 103) {

								price = price - 1.50;
							}
							else if (discount.getDiscountID() == 104) {

								price = price - (price * 0.10);
							}
							else if (discount.getDiscountID() == 105) {

								price = price - (price * 0.20);
							}

							DBNinja.usePizzaDiscount(ret,discount);
						}
					}
				}
				System.out.println("Do you want to add more discounts to this Pizza? Enter y/n?");
				glag = reader.readLine();
			}
		}

		List<Order> orders = DBNinja.getOrders(false);
		int max = 0;
		for (Order order : orders) {

			if (order.getOrderID() > max) {

				max = order.getOrderID();
			}
		}
		max++;
		ret = new Pizza(max + 1, size, crust, orderID, "0", "2023-12-08", price, Math.round(cost * 100.00) / 100.00);

		DBNinja.addPizza(ret);

		return ret;
	}


		public static void PrintReports () throws SQLException, NumberFormatException, IOException
		{
			/*
			 * This method asks the use which report they want to see and calls the DBNinja method to print the appropriate report.
			 *
			 */

			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

			// User Input Prompts...
			System.out.println("Which report do you wish to print? Enter\n(a) ToppingPopularity\n(b) ProfitByPizza\n(c) ProfitByOrderType:");
			String choice = reader.readLine();
			switch (choice.toLowerCase()) {
				case "a":
					DBNinja.printToppingPopReport();
					break;
				case "b":
					DBNinja.printProfitByPizzaReport();
					break;
				case "c":
					DBNinja.printProfitByOrderType();
					break;
				default:
					System.out.println("I don't understand that input... returning to menu...");
			}
		}

		//Prompt - NO CODE SHOULD TAKE PLACE BELOW THIS LINE
		// DO NOT EDIT ANYTHING BELOW HERE, THIS IS NEEDED TESTING.
		// IF YOU EDIT SOMETHING BELOW, IT BREAKS THE AUTOGRADER WHICH MEANS YOUR GRADE WILL BE A 0 (zero)!!

		public static void PrintMenu() {
			System.out.println("\n\nPlease enter a menu option:");
			System.out.println("1. Enter a new order");
			System.out.println("2. View Customers ");
			System.out.println("3. Enter a new Customer ");
			System.out.println("4. View orders");
			System.out.println("5. Mark an order as completed");
			System.out.println("6. View Inventory Levels");
			System.out.println("7. Add Inventory");
			System.out.println("8. View Reports");
			System.out.println("9. Exit\n\n");
			System.out.println("Enter your option: ");
		}

		/*
		 * autograder controls....do not modiify!
		 */

		public final static String autograder_seed = "6f1b7ea9aac470402d48f7916ea6a010";


		private static void autograder_compilation_check () {

			try {
				Order o = null;
				Pizza p = null;
				Topping t = null;
				Discount d = null;
				Customer c = null;
				ArrayList<Order> alo = null;
				ArrayList<Discount> ald = null;
				ArrayList<Customer> alc = null;
				ArrayList<Topping> alt = null;
				double v = 0.0;
				String s = "";

				DBNinja.addOrder(o);
				DBNinja.addPizza(p);
				DBNinja.useTopping(p, t, false);
				DBNinja.usePizzaDiscount(p, d);
				DBNinja.useOrderDiscount(o, d);
				DBNinja.addCustomer(c);
				DBNinja.completeOrder(o);
				alo = DBNinja.getOrders(false);
				o = DBNinja.getLastOrder();
				alo = DBNinja.getOrdersByDate("01/01/1999");
				ald = DBNinja.getDiscountList();
				d = DBNinja.findDiscountByName("Discount");
				alc = DBNinja.getCustomerList();
				c = DBNinja.findCustomerByPhone("0000000000");
				alt = DBNinja.getToppingList();
				t = DBNinja.findToppingByName("Topping");
				DBNinja.addToInventory(t, 1000.0);
				v = DBNinja.getBaseCustPrice("size", "crust");
				v = DBNinja.getBaseBusPrice("size", "crust");
				DBNinja.printInventory();
				DBNinja.printToppingPopReport();
				DBNinja.printProfitByPizzaReport();
				DBNinja.printProfitByOrderType();
				s = DBNinja.getCustomerName(0);
			} catch (SQLException | IOException e) {
				e.printStackTrace();
			}
		}


	}

