#include <stdio.h>
#include <cmath>
void aceleracion(double m[9], double x[9], double y[9], double ax[9], double ay[9]);


//voy a crear un fichero (input) con las condiciones iniciales de los planetas y del sol
//a partir de los datos de ese fichero y del algoritmo de Verlet voy a calcular las siguientes variables
//las voy a ir guardando paso a paso en el nuevo fichero (output), que va a ser el que utilice en el .py
//mi fichero imput esta estructurado así:
//
//    xsol ysol vsolx vsoly masasol
//    xmerc ymerc vmercx vmercy masamerc
//    xvenus yvenus vvenusx vvenusy masaven
//    ...
//
//
//    xnept ynept vneptx vnepty masanept
//
//  todos los datos de mi fichero imput han sido modificados para evitar un error tan grande


int main() {
    // Creo y abro los ficheros que voy a usar
    FILE *input;
    FILE *output;

    input = fopen("ValoresIniciales.txt", "r");
    output = fopen("resultados.txt", "w");

    // Defino mis variables (w es un vector auxiliar)
    double x[9], y[9], vx[9], vy[9], ax[9], ay[9], wx[9], wy[9], m[9];
    double t = 0, h = 0.2; // Inicializo t y defino el paso h
    int i;

    // Inicializo mis vectores con los valores iniciales correspondientes al sol y a cada planeta
    for(i=0; i<9; i++){
        fscanf(input, "%lf\t%lf\t%lf\t%lf\t%lf",&x[i],&y[i],&vx[i],&vy[i],&m[i]);
    }

    //Calculo la aceleracion inicial
    aceleracion(m,x,y,ax,ay);

    // Hago mis cálculos
    // Defino el tmax como 1030 porque es un poco mayor que el tiempo que tarda Neptuno en dar una vuelta al sol
    while (t < 10000) {
        

        // Inicio el bucle para guardar los resultados en los vectores
        for (i = 0;i<9; i++) {
            // Guardo la parte del cálculo relacionada con a(t)
           
            wx[i] = vx[i] + h / 2. * ax[i];
            wy[i] = vy[i] + h / 2. * ay[i];

            // Velocidades en t+h
            vx[i] = vx[i] + h * ax[i];
            vy[i] = vy[i] + h * ay[i];

            // Posición en x e y cuando t+h
            x[i] = x[i] + h * wx[i] + h * h / 2. * ax[i];
            y[i] = y[i] + h * wy[i] + h * h / 2. * ay[i];
            fprintf(output, "%lf,%lf\n", x[i], y[i]);
        }
        fprintf(output, "\n");
        //Calculo la aceleracion en t+h
            aceleracion(m,x,y,ax,ay);
        // Paso al siguiente momento
        t = t + h;
    }

    fclose(input);
    fclose(output);

    return 0;
}

void aceleracion(double m[9],double x[9],double y[9],double ax[9],double ay[9]){
    int i, j;
    
    //Calculo la aceleracion de cada elemento i causada por el resto de elementos j
    for(i=0; i<9; i++){
        ax[i]=0.;
        ay[i]=0.;
        for(j=0; j<9; j++){
            if(j!=i){
                ax[i]=ax[i]+(-m[j]*(x[i]-x[j]))/(1.*pow((pow((x[i]-x[j]),2.)+pow((y[i]-y[j]),2.)),3/2.));
                ay[i]=ay[i]+(-m[j]*(y[i]-y[j]))/(1.*pow((pow((x[i]-x[j]),2.)+pow((y[i]-y[j]),2.)),3/2.));
            }
            
        }
    }
    return;
}

