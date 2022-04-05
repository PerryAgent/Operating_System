#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

using namespace std;

//Defining some global values to be used across all threads
long Finish_Line = 50000000;
long Move = 50;
long Ahead = 25000000;
long hare_counter = 0;
long turtle_counter = 0;

//Mutex for hare, turtle and reporter
pthread_mutex_t turtle_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t hare_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reporter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *god_method(void *ptr)
{
    //To generate random numbers everytime
    srand(time(0));

    cout << "\n\n********GOD HAS STARTED THE RACE********\n\n";

    while (turtle_counter < Finish_Line && hare_counter < Finish_Line)
    {
        //Locking them so that they won't change while God is making a decision
        pthread_mutex_lock(&reporter_mutex);
        pthread_mutex_lock(&turtle_mutex);
        pthread_mutex_lock(&hare_mutex);

        if (rand() % 10 < 2)
        {
            cout << "\n*************GOD HAS INTERVENED*************";

            //Random position till before the finish line for the hare and turtle
            turtle_counter = rand() % (Finish_Line + 1);
            hare_counter = rand() % (Finish_Line + 1);
            cout << "\n\nTurtle is now at " << turtle_counter << "\nHare is now at " << hare_counter << "\n\n";
            cout << "********************************************\n\n";
        }

        //Unlocking them since decision has been made
        pthread_mutex_unlock(&reporter_mutex);
        pthread_mutex_unlock(&turtle_mutex);
        pthread_mutex_unlock(&hare_mutex);

        usleep(5000);
    }

    return (void *)0;
}

void *turtle_method(void *ptr)
{
    //As long as nobody has reached the finish line
    while (turtle_counter < Finish_Line && hare_counter < Finish_Line)
    {
        pthread_mutex_lock(&turtle_mutex);
        turtle_counter += Move * 0.4;
        pthread_mutex_unlock(&turtle_mutex);
    }

    return (void *)0;
}

void *hare_method(void *ptr)
{
    //To generate random numbers everytime
    srand(time(0));

    while (turtle_counter < Finish_Line && hare_counter < Finish_Line)
    {
        //If hare moves ahead of turtle by a fixed nuumber of steps, hare must sleep for some random time
        if (hare_counter - turtle_counter >= Ahead)
            usleep(rand() % (500));

        pthread_mutex_lock(&hare_mutex);
        hare_counter += Move;
        pthread_mutex_unlock(&hare_mutex);
    }

    return (void *)0;
}

void *reporter_method(void *args)
{
    //As long as nobody has reached the finish line
    while (turtle_counter < Finish_Line && hare_counter < Finish_Line)
    {
        //locking the reporter
        pthread_mutex_lock(&reporter_mutex);

        cout << "\nREPORTING THE POSITIONS OF PARTICIPANTS:\n\nTurtle\t: " << turtle_counter << "\nHare\t: " << hare_counter << "\n";

        pthread_mutex_unlock(&reporter_mutex);

        //Letting the thread sleep for some time
        usleep(500);
    }

    //At least one of them has reached the finish line
    cout << "\n*************RACE IS OVER*************\n";

    if (turtle_counter >= Finish_Line && hare_counter >= Finish_Line)
    {
        cout << "\n\n The MATCH is a DRAW!\n";
    }
    else if (turtle_counter >= Finish_Line)
    {
        cout << "\n\n The TURTLE has WON the race!\n";
    }
    else
    {
        cout << "\n\n The HARE has WON the race!\n";
    }

    cout << "\n\n**************************************\n\n";

    return (void *)0;
}

int main()
{

    //Threads for hare, turtle, god and reporter
    pthread_t hare, turtle, god, reporter;

    //Creating the threads
    pthread_create(&god, NULL, god_method, NULL);
    pthread_create(&turtle, NULL, turtle_method, NULL);
    pthread_create(&hare, NULL, hare_method, NULL);
    pthread_create(&reporter, NULL, reporter_method, NULL);

    //Waiting for threads to finish execution of respective methods
    pthread_join(turtle, NULL);
    pthread_join(hare, NULL);
    pthread_join(reporter, NULL);
    pthread_join(god, NULL);

    return 0;
}