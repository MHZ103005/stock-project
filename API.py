import yfinance as yf

tickers = ["AAPL", "MSFT", "GOOG"]
data = yf.download(tickers, period="1d")["Close"].iloc[-1]

for ticker in tickers:
    print(ticker, data[ticker])