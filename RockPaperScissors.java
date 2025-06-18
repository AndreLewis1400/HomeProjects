/*
	Author: Andre Lewis
	Course: COP2250.
	Date: 03/29/2024.
	Assignment: Module 5 | zyLabs (H)
	Instructor: Sergio Pisano.
	Description: 12.1 LAB* (H): Program: Rock paper scissors
 */
import java.util.Scanner;
import java.util.Random;

public class RockPaperScissors {
	public static void main(String[] args) {
		Scanner scnr = new Scanner(System.in);
		final int ROCK = 0;
		final int PAPER = 1;
		final int SCISSORS = 2;
		Random rand = new Random();
		int seed = scnr.nextInt();
		rand.setSeed(seed);


		String[] player = new String[2]; // array holding two players

		//System.out.print("Enter Player 1 name: ");
		player[0] = scnr.next(); // Player 1
		//System.out.print("Enter Player 2 name: ");
		player[1] = scnr.next(); // Player 2

		//System.out.print("Enter the number of rounds: ");
		int rounds = scnr.nextInt(); // Number of rounds
		int i; // index
		boolean tie = false; // player 1 or 2 tie
		int winner0 = 0; // wins for player 1
		int winner1 = 0; // wins for player 2
		int randomNumber0 = rand.nextInt(3), // Player 1 choice
				randomNumber1 = rand.nextInt(3); // Player 2 choice

		while ( rounds < 1) // Validate rounds input
		{
			System.out.println("Rounds must be > 0");
			rounds = scnr.nextInt(); // Number of rounds
		}

		System.out.println(player[0] + " vs " +
				player[1] + " for " + rounds + " rounds"); 

		for (i = 0; i < rounds; ++i)
		{	

			do
			{ 
				do
				{    				
					if (randomNumber0 == ROCK) // player 1 Value
					{}
					else if (randomNumber0 == PAPER) // player 1 Value
					{}
					else if (randomNumber0 == SCISSORS) // player 1 Value
					{}

					//randomNumber1 = rand.nextInt(3); // Generate random numbers 0-2

					if (randomNumber1 == ROCK) // player 2 Value
					{}
					else if (randomNumber1 == PAPER) // player 2 Value
					{}
					else if (randomNumber1 == SCISSORS) // player 2 Value
					{}

					if (randomNumber0 == randomNumber1)
					{
						System.out.println("Tie"); // Output Tie if player 1&2 has matching values
						randomNumber0 = rand.nextInt(3); // Player 1 choice
						randomNumber1 = rand.nextInt(3); // Player 2 choice
						tie = true; // Continue loop
					}


					else if (randomNumber0 != randomNumber1)
					{
						tie = false; // Exit loop
					}


				} while (tie); // Loop control

				// Determine winner based on win-lose relationships and output player winning choice
				if (randomNumber0 == ROCK && randomNumber1 == PAPER) {
					winner1 += 1;
					System.out.println(player[1] + " wins with " + "paper");
				}
				else if (randomNumber0 == PAPER && randomNumber1 == ROCK) {
					winner0 += 1;
					System.out.println(player[0] + " wins with " + "paper");
				}
				else if (randomNumber0 == SCISSORS && randomNumber1 == PAPER) {
					winner0 += 1;
					System.out.println(player[0] + " wins with " + "scissors");
				}
				else if (randomNumber0 == PAPER && randomNumber1 == SCISSORS) {
					winner1 += 1;
					System.out.println(player[1] + " wins with " + "scissors");
				}
				else if (randomNumber0 == SCISSORS && randomNumber1 == ROCK) {
					winner1 += 1;
					System.out.println(player[1] + " wins with " + "rock");
				}
				else if (randomNumber0 == ROCK && randomNumber1 == SCISSORS) {
					winner0 += 1;
					System.out.println(player[0] + " wins with " + "rock");
				}
				//******************************************************************************
				if (randomNumber0 == ROCK) // player 1 Value
				{}
				else if (randomNumber0 == PAPER) // player 1 Value
				{}
				else if (randomNumber0 == SCISSORS) // player 1 Value
				{}

				if (randomNumber1 == ROCK) // player 2 Value
				{}
				else if (randomNumber1 == PAPER) // player 2 Value
				{}
				else if (randomNumber1 == SCISSORS) // player 2 Value
				{}

				if (randomNumber0 == randomNumber1)
				{
					System.out.println("Tie"); // Output Tie if player 1&2 has matching values
					randomNumber0 = rand.nextInt(3); // Player 1 choice
					randomNumber1 = rand.nextInt(3); // Player 2 choice
					tie = true; // Continue loop
				}


				else if (randomNumber0 != randomNumber1)
				{
					tie = false; // Exit loop
				}


			} while (tie); // Loop control
			randomNumber0 = rand.nextInt(3); // Player 1 choice
			randomNumber1 = rand.nextInt(3); // Player 2 choice

		}	
		if (winner0 > winner1)
		{
			System.out.println(player[0] + " wins " + winner0 + " and " + player[1] + " wins " + winner1 );
		}
		else if (winner0 < winner1)
		{
			System.out.println(player[1] + " wins " + winner1 + " and " + player[0] + " wins " + winner0 );
		}
	}
}

/*
82
Anna
Bert
3
Code Output
Anna vs Bert for 3 rounds
Anna wins with paper
Anna wins with paper
Tie
Tie
Anna wins with rock
Anna wins 3 and Bert wins 0
 */
