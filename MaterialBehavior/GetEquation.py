import numpy as np

#list of temperates we have:
#iron and tungsten
T = np.array([10, 20, 50, 100, 200, 300, 400, 600, 800, 1000])
#Copper
T2 = np.array([4.2, 15, 20, 30, 40, 50, 77, 100, 150, 200, 250, 295, 300 ])
#Steel
T3 = np.array([4.2, 10.0, 25.0, 50.0, 77.0, 100.0, 150.0, 200.0, 250.0, 300.0])
#Cupro-Nickel (70/30)
T4 = np.array([4.2, 10.0, 50.0, 77.0, 100.0, 150.0, 200.0, 250.0, 293.15, 300.0])
#Phosphor Bronze and Beryllium Copper
T5 = np.array([4.2, 10.0, 25.0, 50.0, 77.0, 100.0, 150.0, 200.0, 250.0, 300.0])



#add Resistivity (nohm * m)
#use dicinoary -> key is metal name, value is the array that corresponds to temp
metals_data = {
    #"Iron" : np.array([4.054, 4.120, 5.52, 16.62, 56.0, 105.0, 166.1, 334.6, 583.0, 909.0]),
    #"Tungsten": np.array([0.492, 0.554, 3.02, 16.65, 55.5, 97.7, 141.1, 231.7, 325.9, 423.3]),
    #"OFHC Copper (C10100)" : np.array([.338, .34, .348, .398, .538, .828, 2.238, 3.738, 7.338,  10.838, 14.138, 17.238, 17.788]),
    #"Stainless Steel" : np.array([500.00, 501.68, 508.28, 522.77, 541.33, 558.97, 600.67, 646.18, 695.04, 746.89]),
    #"Cupro-Nickel" : np.array([335.09, 335.19, 335.87, 336.33, 336.72, 337.57, 338.42, 339.27, 340.00, 340.12]),
    "Phosphor Bronze" : np.array([102.22, 102.31, 102.91, 104.78, 107.74, 110.80, 118.54, 127.54, 137.66, 148.79]),
    "Beryllium Copper" : np.array([53.26, 53.34, 53.80, 55.15, 57.20, 59.31, 64.64, 70.81, 77.71, 85.25])
    }
#Degree want polynomial to be up to
degree = 3
#store models
#kinda scuffed, got to re run it for the metal you want and make new temp array
calculated_models = {}
for metal_name, R_value in metals_data.items():
    coefficients = np.polyfit(T5, R_value, degree)
    calculated_models[metal_name] = coefficients

    print(f"--- {metal_name} ---")
    print(f"A (x^3): {coefficients[0]:.4e}")
    print(f"B (x^2): {coefficients[1]:.4e}")
    print(f"C (x^1): {coefficients[2]:.4e}")
    print(f"D (x^0): {coefficients[3]:.4e}\n")
