# Commission-Based-Investment-Company-Simulator in C

## Overview
The **Commission-Based-Investment-Company-Simulator** is a C-based program designed to simulate a commission-based investment model where a company's head, employees, and rookies interact through investments, commissions, and wealth distribution. The simulator operates by:

1. **Company Setup**: The head of the company can recruit employees, who can then recruit rookies.
2. **Investment and Profit Generation**: Each participant in the hierarchy can invest money, and profits or losses are calculated based on the amount invested.
3. **Commission System**: Commissions are calculated at each level of the hierarchy:
   - **Head (Level 0)**: 20% commission
   - **Employee (Level 1)**: 10% commission
   - **Rookie (Level 2)**: 5% commission

4. **Wealth Distribution**: The program distributes wealth according to the performance of investments and commissions, with the head of the company benefiting the most due to the hierarchical structure.

## Purpose
This program simulates a multi-level investment structure, allowing users to visualize how wealth is distributed based on investment and commission at each level. It focuses on showing the power dynamics in a commission-based hierarchy, with various stages of investment growth.

---

## Header Files

### `file.h`
The `file.h` header file is responsible for managing file operations in the simulator. It handles reading, writing, and manipulating data related to company members and their financial details. This file ensures that data can be saved and loaded between program sessions.


