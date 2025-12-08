import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/equity_curve.csv", parse_dates=["date"])
df.set_index("date", inplace=True)

plt.plot(df["equity"])
plt.title("Equity Curve")
plt.xlabel("Date")
plt.ylabel("Equity")
plt.grid(True)

plt.gcf().autofmt_xdate()
plt.tight_layout()
plt.savefig("analysis/equity_curve.png")
