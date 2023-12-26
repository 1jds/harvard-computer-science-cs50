import csv
from cs50 import SQL
from os import path, system


def main(FILENAME="./tickers/company-symbols.csv", DB_NAME="finance.db"):
    # Create list of dictionaries containing company data // Ticker,Name,Exchange
    ticker_data = []

    # Open CSV file
    try:
        with open(FILENAME, "r") as company_info_file:
            # Create DictReader
            company_info_reader = csv.DictReader(company_info_file)

            # Iterate over CSV file, to insert info into database
            for row in company_info_reader:
                ticker_data.append(row)
    except:
        print("An error has occured while opening the file")
        return 1

    # Open database
    if path.exists(DB_NAME):
        db = SQL(f"sqlite:///{DB_NAME}")
    else:
        print("Database not found")
        return 1

    # Insert company data into database
    for ticker in ticker_data:
        # Insert ticker and company name into companies table
        db.execute(
            "INSERT OR IGNORE INTO companies (ticker, company_name) VALUES (?, ?)",
            ticker["ticker"],
            ticker["name"],
        )

    print("Insertion of data into database complete")
    return 0


if __name__ == "__main__":
    main()
