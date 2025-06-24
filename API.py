import yfinance as yf
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

def fetchPrices(inFile = "tickers.txt", outFile = "prices.txt"):
    with open(inFile, "r") as f:
        line = f.readline().strip()
        tickers = line.split()
        f.truncate(0)
    
    with open(outFile, "w") as out:
        for ticker in tickers:
            try:
                stock = yf.Ticker(ticker)
                price = stock.history(period = "1d")["Close"].iloc[-1]
                out.write(f"{price}\n")
            except:
                out.write("Ticker does not exist!")


fetchPrices()
print("File updated")

