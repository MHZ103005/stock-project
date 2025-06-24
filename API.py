import yfinance as yf
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

def fetchPrices(inFile = "tickers.txt", outFile = "prices.txt"):
    with open(inFile, "r+") as f: #opens the input file and converts all tickers into an array
        line = f.readline().strip()
        if not line:        #if file is empty return
            print("empty file")
            return
        tickers = line.split()
        f.seek(0)
        f.truncate(0) #clears the input file for next use
    
    with open(outFile, "w") as out:
        for ticker in tickers: #runs through array of tickers
            try:
                stock = yf.Ticker(ticker)
                price = stock.history(period = "1d")["Close"].iloc[-1] #API call
                out.write(f"{price}\n") #write the price in a new line in output file
            except:
                out.write("Ticker does not exist!") #error handling


class FileWatcher(FileSystemEventHandler): #File watcher from watchdog, only action is file is modified
    def on_modified(self, event):
        if event.src_path.endswith("tickers.txt"):
            print("Calling API")
            fetchPrices()
            print("File updated")

if __name__ == "__main__":
    callComplete = False
    filePath = "."
    fileWatcher = FileWatcher()
    observer = Observer()
    observer.schedule(fileWatcher, path = filePath, recursive=False)
    observer.start()

    try:
        while not callComplete:
            time.sleep(1) #keep program looping
    except KeyboardInterrupt:
        observer.stop()
    
    observer.join()
    print("Program Ended")
    quit()
