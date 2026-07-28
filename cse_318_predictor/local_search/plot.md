How to Use in Your Project

    Save the above Python script as generate_plots.py in your working directory.

    Ensure your actual CSV benchmark file is saved in the same directory as 2205040.csv.

    Run the script:
    Bash

    python generate_plots.py

    Embed max_cut_comparison.png into your LaTeX report or document.
    """

with open("plot.md", "w", encoding="utf-8") as f:
f.write(content)

print("plot.md file generated successfully.")


```text?code_stdout&code_event_index=1
plot.md file generated successfully.

Your plot.md file has been generated for your AI agent.
MD icon
plot
 MD 

Below is the complete text contents of the plot.md file for reference:
Markdown

# Plot Generation Instructions & Python Script (`plot.py`)

This document provides clear instructions and a complete Python script to load the Max-Cut algorithm benchmark results from a CSV file (`2205040.csv`) and generate comparative bar charts as required by the assignment guidelines.

---

## 1. Overview of Requirements

The report requires plots or visualizations demonstrating how various heuristic and metaheuristic algorithms perform for the **Max-Cut Problem** across different benchmark graphs ($G_1$ through $G_{10}$ or more).

### Target CSV Schema
The CSV file (e.g., `2205040.csv`) has the following column headers:
1. `Name` (Graph ID, e.g., G1, G2, ...)
2. `|V| or n` (Number of vertices)
3. `|E| or m` (Number of edges)
4. `Simple Randomized`
5. `Simple Greedy`
6. `Semi-greedy (α = 0.6)`
7. `Simple Local - No. of iterations`
8. `Simple Local - Average value`
9. `GRASP (300 iterations) - Best value`
10. `Known best solution or upper bound`

---

## 2. Visualization Specifications

The generated plot matches the requirements shown in the assignment reference image:

- **Chart Type:** Grouped Bar Chart (Clustered Column Chart).
- **X-Axis:** Graph Name (`G1`, `G2`, `G3`, ..., `G10`).
- **Y-Axis:** Max Cut Value (or Objective Value).
- **Algorithms Compared:**
  - Simple Randomized
  - Simple Greedy
  - Semi-greedy ($\alpha = 0.6$)
  - Simple Local (Average value)
  - GRASP (300 iterations)
  - *(Optional)* Known best solution / Upper bound (represented as benchmark baseline points or additional bars).
- **Visual Styling:**
  - Dark or professional clean theme.
  - Distinct color palette for each algorithm.
  - Clear legend at the bottom or top.
  - High resolution (300 DPI) output suitable for PDF inclusion.

---

## 3. Python Implementation Script (`generate_plots.py`)

Below is the complete, self-contained Python script using `pandas`, `matplotlib`, and `seaborn` to parse the CSV and save the output figure (`max_cut_comparison.png`).

```python
import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def generate_max_cut_plot(csv_file_path="2205040.csv", output_image_path="max_cut_comparison.png"):
    # 1. Read CSV Data
    if not os.path.exists(csv_file_path):
        # Create dummy sample data matching user's CSV structure if file doesn't exist
        sample_data = {
            "Name": [f"G{i}" for i in range(1, 11)],
            "|V| or n": [800]*10,
            "|E| or m": [19176]*10,
            "Simple Randomized": [9590, 9587, 9600, 9550, 9580, 1200, 1180, 1190, 1210, 1205],
            "Simple Greedy": [10967, 11036, 10980, 11010, 10950, 1450, 1420, 1400, 1460, 1430],
            "Semi-greedy (α = 0.6)": [11218, 11186, 11250, 11200, 11190, 1550, 1520, 1510, 1560, 1540],
            "Simple Local - No. of iterations": [129, 136, 130, 128, 135, 45, 42, 40, 48, 44],
            "Simple Local - Average value": [11327, 11396, 11340, 11380, 11310, 1620, 1600, 1580, 1630, 1610],
            "GRASP (300 iterations) - Best value": [11475, 11486, 11500, 11460, 11480, 1720, 1690, 1680, 1710, 1700],
            "Known best solution or upper bound": [12078, 12084, 12100, 12050, 12090, 2000, 1950, 1940, 1980, 1960]
        }
        df = pd.DataFrame(sample_data)
        df.to_csv(csv_file_path, index=False)
        print(f"Sample '{csv_file_path}' generated.")
    else:
        df = pd.read_csv(csv_file_path)

    # 2. Select Relevant Algorithms for Plotting
    # Clean column names by stripping extra whitespaces
    df.columns = [c.strip() for c in df.columns]

    graphs = df['Name'].values
    
    # Map CSV columns to plotting labels
    algo_columns = {
        'Simple Randomized': 'Randomized',
        'Simple Greedy': 'Greedy',
        'Semi-greedy (α = 0.6)': 'Semi-Greedy',
        'Simple Local - Average value': 'Local Search',
        'GRASP (300 iterations) - Best value': 'GRASP'
    }

    # Verify columns exist
    valid_algos = {col: label for col, label in algo_columns.items() if col in df.columns}

    # 3. Setup Plot Appearance
    plt.style.use('dark_background') # Styling matching the black background dark theme in reference image
    fig, ax = plt.subplots(figsize=(12, 6), dpi=300)

    # Set background colors explicitly
    fig.patch.set_facecolor('#222222')
    ax.set_facecolor('#222222')

    x = np.arange(len(graphs))
    num_algos = len(valid_algos)
    bar_width = 0.15

    # Define color scheme similar to reference plot
    colors = ['#3a82c4', '#d96b27', '#a5a5a5', '#edb120', '#41719c', '#70ad47']

    # 4. Plot Bars for each Algorithm
    for idx, (col_name, label) in enumerate(valid_algos.items()):
        offset = (idx - num_algos / 2) * bar_width + bar_width / 2
        values = df[col_name].values
        ax.bar(x + offset, values, width=bar_width, label=label, color=colors[idx % len(colors)], edgecolor='none')

    # Optional: Plot Best Known Upper Bound as line markers
    if 'Known best solution or upper bound' in df.columns:
        ax.plot(x, df['Known best solution or upper bound'].values, color='#ff4d4d', marker='o', linestyle='--', linewidth=1.5, label='Upper Bound')

    # 5. Formatting & Labels
    ax.set_title("Max Cut (Graph 1-10)", fontsize=16, fontweight='bold', pad=15, color='white')
    ax.set_xticks(x)
    ax.set_xticklabels(graphs, fontsize=11, color='white')
    ax.tick_params(axis='y', colors='white', labelsize=10)
    
    # Custom Grid Lines
    ax.yaxis.grid(True, linestyle='-', color='#444444', alpha=0.7)
    ax.set_axisbelow(True)

    # Remove unnecessary spines
    for spine in ['top', 'right', 'left', 'bottom']:
        ax.spines[spine].set_color('#444444')

    # Legend at Bottom
    legend = ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.12), ncol=len(valid_algos)+1, frameon=False, fontsize=10)
    for text in legend.get_texts():
        text.set_color("white")

    plt.tight_layout()

    # 6. Save Plot
    plt.savefig(output_image_path, dpi=300, facecolor=fig.get_facecolor(), edgecolor='none', bbox_inches='tight')
    plt.close()
    print(f"Plot successfully saved to {output_image_path}")

if __name__ == "__main__":
    generate_max_cut_plot()

4. How to Use in Your Project

    Save the above Python script as generate_plots.py in your working directory.

    Ensure your actual CSV benchmark file is saved in the same directory as 2205040.csv.

    Run the script:
    Bash

    python generate_plots.py