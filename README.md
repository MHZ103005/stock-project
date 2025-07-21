# Asset Monitor

**Asset Monitor** is a lightweight C++ application that allows users to **track assets** and **simulate paper trading** using real market data. With a simple interface and persistent storage via SQLite, you can monitor the value of your portfolio over time and keep track of gains and losses without risking real money.

## 📌 Features

- 💼 **Portfolio Management**: Add, update, and view your asset holdings  
- 📊 **Live Price Tracking**: Get real-time asset prices using the Alpha Vantage API (via Python + yFinance)  
- 📈 **Net Worth Calculation**: See your total portfolio value and profit/loss breakdown  
- 📝 **Paper Trading Mode**: Simulate trades with a virtual balance to test strategies risk-free  

## 🛠️ Tech Stack

- **C++** – core application logic and user interface  
- **Python** – used alongside `yFinance` to retrieve real market data  
- **SQLite** – stores user portfolios, asset data, and simulated trades  

## 🚀 Getting Started

There are no special dependencies or tools required. Just compile the C++ source files and ensure Python with `yfinance` is installed.

1. Clone the repo  
2. Compile the C++ files using `g++` or a Makefile  
3. Ensure Python 3 and `yfinance` are installed  
4. Run the app and start tracking!

```bash
pip install yfinance
g++ main.cpp -o AssetMonitor
./AssetMonitor
```
## 👤Author
Made by Michael Zheng
