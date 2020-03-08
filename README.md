# vending_machine by Segmentation Fault

**Project realized for the eliminatory test of the Hackathon &quot;HackITAll&quot; 2020        by team Segmentation Fault**

**GitHub link:** [https://github.com/24makee/vending\_machine](https://github.com/24makee/vending_machine)

**Overview**

This project has the goal to simulate, as best as possible, what a person is experiencing when buying something from a vending machine. From the choice of changing the payment method whenever the user want and even getting their money back, to the freedom of introducing any amount of money and getting all the change back.

**Description of the project**

From the beginning we are welcomed by the screen of all possible items that can be bought and we are asked to choose a payment method.

For cash payment, we can insert as many bills as we want, after every bill we are asked if we want to insert more or if we want to cancel the transaction. After inserting the money we have to choose a product, if we have entered enough money for a certain product, the product is being delivered and change is returned (if it&#39;s necessary).

For credit card payment, we choose the product first and after that we have to insert a pin, which for security reasons it&#39;s seen by the user as \* for every digit inserted. If a digit of the pin was wrong inserted, the user can press &#39;x&#39; and the transaction will be cancelled.

**Features**

- Implemented administrator panel for supply, accessed only with password
- Transactions details (payment method, code of the purchased product, time of the purchase) are exported in a _.csv_ file, which is created immediately if it doesn&#39;t exist already on the system, easy to manage.
- Errors exported in a text file, errors like:
  - Insufficient funds on the credit card that was used for purchase
  - The impossibility of accessing the _.csv_ file, the product catalog file, or the banking information file
- User&#39;s balance it&#39;s updated immediately after a transaction
- In case of &quot;Out of stock&quot; products, the menu updates in real time, after the transaction is successful without restarting the program.


**More info in documentation file**
 
**Authors of the project**

- **Andrei Machedon**
  - University POLITEHNICA of Bucharest – Faculty of Automatic Control and Computers
- **Mihnea Constantinescu**
  - University POLITEHNICA of Bucharest – Faculty of Automatic Control and Computers
- **Marius Antache**
  - University POLITEHNICA of Bucharest – Faculty of Automatic Control and Computers
