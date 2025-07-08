#include "sqlfunc.h"

bool tickerExists(const std::string &ticker)
{
    std::fstream file("tickers.txt");
    file << ticker << std::endl;
    file.close();

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate waiting for API response
    file.open("prices.txt");
    std::string line;
    std::getline(file, line);
    file.close();
    if (line == "F")
    {
        return false;
    }

    return true;
}

// Insert functions
void insertUser(sqlite3 *db, const std::string &username, double balance)
{
    std::string sql =
        "INSERT INTO users (username, balance) VALUES ('" + username + "', " + std::to_string(balance) + ");";

    char *errMsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Insert user failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "User inserted: " << username << std::endl;
    }
}

void insertAsset(sqlite3 *db, int userId, const std::string &ticker, double quantity)
{
    std::string sql = "INSERT INTO assets (user_id, ticker, quantity) VALUES (" + std::to_string(userId) + ", '" +
                      ticker + "', " + std::to_string(quantity) + ");";

    char *errMsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Insert asset failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Asset inserted: " << ticker << " for user " << userId << std::endl;
    }
}
// could optimize this by updating the table instead of deleting and inserting
void deleteAssets(sqlite3 *db, int userId)
{
    std::string sql = "DELETE FROM assets WHERE user_id = " + std::to_string(userId) + ";";

    char *errMsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Delete asset failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void insertTrade(sqlite3 *db, int userId, const std::string &ticker, const std::string &action, double quantity,
                 double price)
{
    std::string sql = "INSERT INTO trades (user_id, ticker, action, quantity, price) VALUES (" +
                      std::to_string(userId) + ", '" + ticker + "', '" + action + "', " + std::to_string(quantity) +
                      ", " + std::to_string(price) + ");";

    char *errMsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Insert trade failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Trade recorded: " << action << " " << ticker << std::endl;
    }
}
int retrieveUserID(sqlite3 *db, const std::string &username)
{
    std::string sql = "SELECT id FROM users WHERE username = '" + username + "';";
    char *errMsg = nullptr;
    int userId = -1; // Default to -1 if not found

    auto callback = [](void *data, int argc, char **argv, char **) -> int
    {
        int *id = static_cast<int *>(data);
        if (argc > 0 && argv[0])
        {
            *id = std::stoi(argv[0]);
        }
        return 0;
    };

    if (sqlite3_exec(db, sql.c_str(), callback, &userId, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return userId;
}
// checks if username exists currently
bool checkUsername(sqlite3 *db, const std::string &username)
{
    std::string sql = "SELECT 1 FROM users WHERE username = '" + username + "';";
    char *errMsg = nullptr;
    bool found = false;

    auto callback = [](void *data, int, char **, char **) -> int { // Callback function returns true if username exists
        *static_cast<bool *>(data) = true;
        return 0;
    };

    if (sqlite3_exec(db, sql.c_str(), callback, &found, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return found;
}
// loads all portfolio assets into vectors
void loadPortfolio(sqlite3 *db, int userid, std::vector<std::string> &tickers, std::vector<double> &quantities)
{
    std::string sql = "SELECT ticker, quantity FROM assets where user_id = " + std::to_string(userid) + ";";
    char *errMsg = nullptr;

    auto callback = [](void *data, int argc, char **argv, char **colNames) -> int
    {
        auto *resultPair = static_cast<std::pair<std::vector<std::string> *, std::vector<double> *> *>(data);
        resultPair->first->emplace_back(argv[0]);
        resultPair->second->emplace_back(std::stod(argv[1]));

        return 0;
    };
    // creat the pair
    std::pair<std::vector<std::string> *, std::vector<double> *> resultPair(&tickers, &quantities);

    if (sqlite3_exec(db, sql.c_str(), callback, &resultPair, &errMsg) != SQLITE_OK)
    {
        std::cerr << "portfolioerror " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}
// print purchase history
void printPurchaseLog(sqlite3 *db, int userid)
{
    std::string sql = "SELECT * FROM trades where user_id = " + std::to_string(userid) + ";";
    char *errMsg = nullptr;

    std::cout << "Here is your purchase log" << std::endl
              << std::endl;

    std::cout << "#   Ticker   Action   Quantity   Price" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    auto callback = [](void *data, int argc, char **argv, char **colNames) -> int
    {
        int *d = static_cast<int *>(data);
        *d += 1;
        std::cout << *d << "       ";
        for (int i = 2; i < argc; i++)
        {
            std::cout << argv[i] << "     ";
        }
        std::cout << std::endl;
        return 0;
    };

    int rowCount = 0; // to count rows
    if (sqlite3_exec(db, sql.c_str(), callback, &rowCount, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Error printing purchase log: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Total trades: " << rowCount << std::endl;
    }
}

// initial database setup
void initializeDatabase(sqlite3 *db)
{
    // Table that stores user information
    // Username corresponds to ID in assets and trades tables
    const char *usersTable = R"( 
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            balance REAL DEFAULT 10000.0
        );
    )";
    // Addets based on user ID
    const char *assetsTable = R"(
        CREATE TABLE IF NOT EXISTS assets (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            ticker TEXT NOT NULL,
            quantity REAL,
            FOREIGN KEY (user_id) REFERENCES users(id)
        );
    )";
    // Trades based on user ID
    const char *tradesTable = R"(
        CREATE TABLE IF NOT EXISTS trades (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            ticker TEXT,
            action TEXT,
            quantity REAL,
            price REAL,
            FOREIGN KEY (user_id) REFERENCES users(id)
        );
    )";

    char *errMsg = nullptr;

    // Run each table creation command
    if (sqlite3_exec(db, usersTable, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Users table error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    if (sqlite3_exec(db, assetsTable, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Assets table error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    if (sqlite3_exec(db, tradesTable, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Trades table error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    std::cout << "Database initialized with users, assets, and trades tables.\n";
}
