#include<stdio.h>
#include<conio.h>
#include<math.h>
#include <cstdlib>
#include <iostream>

#define DIMENSIONS 2
#define MAX_ITERATIONS 20
#define SWARM_SIZE 5

#define UPPER_BOUND 5.0
#define LOWER_BOUND -5.0
#define CORRECTION_FACTOR 1.5
#define INERTIA_WEIGHT 0.9

using namespace std;
class Swarm{
    public:
    double position[DIMENSIONS];
    double velocity[DIMENSIONS];
    double fitness;
    double pbest[DIMENSIONS];
    double pworst[DIMENSIONS];



    double positionupdate(double velocity, double position)
    {
        double ans = position + velocity;
        return ans;
    }

};
double positionupdate(double velocity, double position)
    {
        double ans = position + velocity;

        if(ans > UPPER_BOUND)
        {
            return 5.000;
        }
        if(ans < LOWER_BOUND)
        {
            return -5.000;
        }
        return ans;
    }
double grd(double , double);
double velocityupdate(double position,double velocity,double gbest,double pbest )
    {
        double r1 = grd(0,1);
        double r2 = grd(0,1);
        double x = position;
        double v = velocity;
        double pb = pbest;
        double pg = gbest;
        double c = CORRECTION_FACTOR;
        double w = INERTIA_WEIGHT;

        double ans = (w * v)+((c * r1)*(pb - x))+((c * r2)*(pg - x));

        return ans;
    }
double grd(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
double calfitness(double x1, double x2)
    {

        double ans = (x1 * x1)-(x1 * x2)+(x2*x2)+(2 * x1)+(4 * x2)+3;
        //double ans = (x1 * x1)-(x1 * x2)+(x2*x2)+(0.1* x1)+(0.7* x2)+0.2;
        return ans;
    }
int main()
{
    int gbest_particle;
    int gworst_particle;

    Swarm particles[SWARM_SIZE];
    //Intialising first Iteration;
    printf("Iteration 1: ");
    for(int i = 0; i < SWARM_SIZE;i++)
    {

        particles[i].position[0] = grd(LOWER_BOUND,UPPER_BOUND);
        particles[i].position[1] = grd(LOWER_BOUND,UPPER_BOUND);
        particles[i].pbest[0] = particles[i].position[0];
        particles[i].pbest[1] = particles[i].position[1];
        particles[i].pworst[0] = particles[i].position[0];
        particles[i].pworst[1] = particles[i].position[1];
        particles[i].fitness = calfitness(particles[i].position[0],particles[i].position[1]);
        particles[i].velocity[0] = grd(0,1);
        particles[i].velocity[1] = grd(0,1);
        //printf("\nParticle %d: x,y = (%lf, %lf) pbest = (%lf, %lf) ",i+1,particles[i].position[0],particles[i].position[1],particles[i].pbest[0],particles[i].pbest[1]);

    }
    gbest_particle = 0;
    for(int i = 0; i < SWARM_SIZE;i++)
    {
        if(particles[i].fitness > particles[gbest_particle].fitness)
        {
            gbest_particle = i;
        }
    }

    gworst_particle = 0;
    for(int i = 0; i < SWARM_SIZE;i++)
    {
        if(particles[i].fitness < particles[gworst_particle].fitness)
        {
            gworst_particle = i;
        }
    }

printf(" \nGWORST: %lf %lf Fitness:%lf",particles[gworst_particle].position[0],particles[gworst_particle].position[1],particles[gworst_particle].fitness);
printf(" \nGBEST: %lf %lf Fitness:%lf",particles[gbest_particle].position[0],particles[gbest_particle].position[1],particles[gbest_particle].fitness);


    //Further Iterations
for(int k = 1; k < MAX_ITERATIONS;k++){

    printf("\nIteration %d: ",k+1);
    for(int j = 0; j < SWARM_SIZE;j++)
    {

    particles[j].velocity[0] = velocityupdate(particles[j].position[0],particles[j].velocity[0],particles[gbest_particle].position[0],particles[j].pbest[0]);
    particles[j].velocity[1] = velocityupdate(particles[j].position[1],particles[j].velocity[1],particles[gbest_particle].position[1],particles[j].pbest[1]);
    particles[j].position[0] = positionupdate(particles[j].velocity[0],particles[j].position[0]);
    particles[j].position[1] = positionupdate(particles[j].velocity[1],particles[j].position[1]);
    double currfit = calfitness(particles[j].position[0],particles[j].position[1]);
    if(particles[j].fitness < currfit)
    {
        particles[j].pbest[0] = particles[j].position[0];
        particles[j].pbest[1] = particles[j].position[1];
    }
    if(particles[j].fitness > currfit)
    {
        particles[j].pworst[0] = particles[j].position[0];
        particles[j].pworst[1] = particles[j].position[1];
    }
    particles[j].fitness = currfit;
    //printf("\nParticle %d: x,y = (%lf, %lf) pbest = (%lf, %lf) Fitness:%lf ",j+1,particles[j].position[0],particles[j].position[1],particles[j].pbest[0],particles[j].pbest[1],particles[j].fitness);

    }
    double prevgbest = particles[gbest_particle].fitness;
    double prevgworst = particles[gworst_particle].fitness;
    for(int i = 0; i < SWARM_SIZE;i++)
    {
        if(particles[i].fitness > particles[gbest_particle].fitness)
        {
            gbest_particle = i;
        }
    }

    for(int i = 0; i < SWARM_SIZE;i++)
    {
        if(particles[i].fitness < particles[gworst_particle].fitness)
        {
            gworst_particle = i;
        }
    }

    printf(" \nGWORST: %lf %lf Fitness:%lf",particles[gworst_particle].position[0],particles[gworst_particle].position[1],particles[gworst_particle].fitness);
    printf(" \nGBEST: %lf %lf Fitness:%lf",particles[gbest_particle].position[0],particles[gbest_particle].position[1],particles[gbest_particle].fitness);

    if((prevgbest == particles[gbest_particle].fitness))
    {
        return 0;
    }

}

    return 0;
}
