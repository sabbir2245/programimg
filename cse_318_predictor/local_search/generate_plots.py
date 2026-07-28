import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def generate_max_cut_plot(csv_file_path="2205040.csv", output_image_path="max_cut_comparison.png"):
    if not os.path.exists(csv_file_path):
        sample_data = {
            "Name": [f"G{i}" for i in range(1, 11)],
            "|V| or n": [800]*10,
            "|E| or m": [19176]*10,
            "Simple Randomized": [9590, 9587, 9600, 9550, 9580, 1200, 1180, 1190, 1210, 1205],
            "Simple Greedy": [10967, 11036, 10980, 11010, 10950, 1450, 1420, 1400, 1460, 1430],
            "Semi-greedy (\u03b1 = 0.6)": [11218, 11186, 11250, 11200, 11190, 1550, 1520, 1510, 1560, 1540],
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

    df.columns = [c.strip() for c in df.columns]

    graphs = df['Name'].values

    algo_columns = {
        'Simple Randomized': 'Randomized',
        'Simple Greedy': 'Greedy',
        'Semi-greedy (\u03b1 = 0.6)': 'Semi-Greedy',
        'Simple Local - Average value': 'Local Search',
        'GRASP (300 iterations) - Best value': 'GRASP'
    }

    valid_algos = {col: label for col, label in algo_columns.items() if col in df.columns}

    plt.style.use('dark_background')
    fig, ax = plt.subplots(figsize=(12, 6), dpi=300)

    fig.patch.set_facecolor('#222222')
    ax.set_facecolor('#222222')

    x = np.arange(len(graphs))
    num_algos = len(valid_algos)
    bar_width = 0.15

    colors = ['#3a82c4', '#d96b27', '#a5a5a5', '#edb120', '#9b59b6', '#70ad47']

    for idx, (col_name, label) in enumerate(valid_algos.items()):
        offset = (idx - num_algos / 2) * bar_width + bar_width / 2
        values = df[col_name].values
        ax.bar(x + offset, values, width=bar_width, label=label, color=colors[idx % len(colors)], edgecolor='none')

    ax.set_title("Max Cut (Graph 1-10)", fontsize=16, fontweight='bold', pad=15, color='white')
    ax.set_xticks(x)
    ax.set_xticklabels(graphs, fontsize=8, color='white', rotation=45)
    ax.tick_params(axis='y', colors='white', labelsize=10)

    ax.yaxis.grid(True, linestyle='-', color='#444444', alpha=0.7)
    ax.set_axisbelow(True)

    for spine in ['top', 'right', 'left', 'bottom']:
        ax.spines[spine].set_color('#444444')

    legend = ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.12), ncol=len(valid_algos), frameon=False, fontsize=10)
    for text in legend.get_texts():
        text.set_color("white")

    plt.tight_layout()

    plt.savefig(output_image_path, dpi=300, facecolor=fig.get_facecolor(), edgecolor='none', bbox_inches='tight')
    plt.close()
    print(f"Plot successfully saved to {output_image_path}")

if __name__ == "__main__":
    generate_max_cut_plot()
