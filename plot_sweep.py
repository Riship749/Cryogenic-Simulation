import pandas as pd
import matplotlib.pyplot as plt

def main():
    print("Loading simulation data...")
    # 1. Load the CSV data
    try:
        df = pd.read_csv('ac_sweep_results.csv')
    except FileNotFoundError:
        print("Error: Could not find 'ac_sweep_results.csv'. Make sure you are in the right directory.")
        return

    # Convert Frequency from Hz to GHz for a much cleaner X-axis on your slides
    df['Frequency_GHz'] = df['Frequency_Hz'] / 1e9

    # 2. Set up the presentation plot style
    plt.figure(figsize=(10, 6))
    
    # 3. Plot the Classical line (Room Temp)
    # Using a dashed red line to represent standard, high-loss resistance
    plt.plot(df['Frequency_GHz'], df['Class_Mag_dB'], 
             label='Classical (300K - Bulk Steel)', 
             color='#e74c3c', linewidth=3, linestyle='--')

    # 4. Plot the Quantum line (Cryogenic)
    # Using a solid blue line to represent the low-loss quantum transmission
    plt.plot(df['Frequency_GHz'], df['Quant_Mag_dB'], 
             label='Quantum (1.2K - Landauer Formalism)', 
             color='#2980b9', linewidth=3)

    # 5. Format labels, title, and legend for a presentation
    plt.title('AC Sweep Analysis: Classical vs. Quantum Impedance', fontsize=16, fontweight='bold', pad=15)
    plt.xlabel('Frequency (GHz)', fontsize=14, fontweight='bold')
    plt.ylabel('Magnitude (dB)', fontsize=14, fontweight='bold')
    
    # Set y-axis limits to frame the 70dB gap nicely
    plt.ylim(0, 200)
    
    # Make the ticks larger and easier to read from the back of a room
    plt.xticks(fontsize=12)
    plt.yticks(fontsize=12)
    
    # Add a grid for easier visual tracing
    plt.grid(True, linestyle=':', alpha=0.7)
    plt.legend(fontsize=12, loc='center right')

    # 6. Save the graph as a high-res image and display it
    output_image = 'presentation_graph.png'
    plt.tight_layout()
    plt.savefig(output_image, dpi=300) # 300 DPI ensures it stays sharp on a projector
    print(f"Success! Graph saved as '{output_image}'.")
    
    plt.show()

if __name__ == "__main__":
    main()