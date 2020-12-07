#include <bits/stdc++.h>
#define debug(x) cout << #x << " : " << x << endl;
#define input_size 10000
#define size_layer_1 100
#define size_layer_2 100
#define size_layer_3 100
#define size_layer_4 100
#define output_size 8
using namespace std;

class rede
{
    private:
        void copy_bias_weights(int weights_layer[][], int bias_layer[],
                               int weights_layer_p[][], int bias_layer_p[]){
            for (int i = 0; i < input_size; i++)
            {
                bias_layer[i] = bias_layer_p[i] 
                for (int j = 0; j < size_layer_1; j++)
                {
                    weights_layer[i][j] = weights_layer_p[i][j];
                }
            }
        }

        int *calculate_w_b_i(int weights_layer[][], int bias_layer[],
                             int inp_lay[], int lin, int col){
            /*
                lin - numero de linhas da matriz
                col - numero de colunas da matriz
                weights_layer - matriz de layers (lin x col)
                inp_lay - layer de input (col x 1)
                bias_layer - matriz de bias (lin x 1)

                return ((weights_layer x inp_lay) + bias_layer) 
                dimensions (lin x 1)  
            */

            int out_lay[lin];
            memset(out_lay, 0, lin * sizeof(int));
            for (int i = 0; i < lin; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    out_lay[i] += weights_layer[i][j] * inp_lay[j];   
                }
                out_lay[i] += bias_layer[i];
                // aplicando sigmoide no resultado gerado
                out_lay[i] = sigmoid(out_lay[i]);
            }

            return out_lay;
        }
    
    public:
        int weights_layer_1[input_size][size_layer_1];
        int bias_layer_1[size_layer_1];

        int weights_layer_2[size_layer_1][size_layer_2];
        int bias_layer_2[size_layer_2];

        int weights_layer_3[size_layer_2][size_layer_3];
        int bias_layer_3[size_layer_3];

        int weights_layer_4[size_layer_3][size_layer_4];
        int bias_layer_4[size_layer_4];

        int weights_output[size_layer_4][output_size];
        int bias_output[output_size];
        

        rede(int weights_layer_1_p[][],int bias_layer_1_p[],int weights_layer_2_p[][],int bias_layer_2_p[],
             int weights_layer_3_p[][],int bias_layer_3_p[],int weights_layer_4_p[][],int bias_layer_4_p[],
             int weights_output_p[][],int bias_output_p[] ){

            copy_bias_weights(weights_layer_1, bias_layer_1, weights_layer_1_p, bias_layer_1_p);
            copy_bias_weights(weights_layer_2, bias_layer_2, weights_layer_2_p, bias_layer_2_p);
            copy_bias_weights(weights_layer_3, bias_layer_3, weights_layer_3_p, bias_layer_3_p);
            copy_bias_weights(weights_layer_4, bias_layer_4, weights_layer_4_p, bias_layer_4_p);
            copy_bias_weights(weights_output, bias_output, weights_output_p, bias_output_p);

        //     for (int i = 0; i < input_size; i++)
        //     {
        //         bias_layer_1[i] = bias_layer_1_p[i] 
        //         for (int j = 0; j < size_layer_1; j++)
        //         {
        //             weights_layer_1[i][j] = weights_layer_1_p[i][j];
        //         }
        //     }
            
        //     for (int i = 0; i < size_layer_1; i++)
        //     {
        //         bias_layer_2[i] = bias_layer_2_p[i] 
        //         for (int j = 0; j < size_layer_2; j++)
        //         {
        //             weights_layer_2[i][j] = weights_layer_2_p[i][j];
        //         }
        //     }

        //     for (int i = 0; i < size_layer_2; i++)
        //     {
        //         bias_layer_3[i] = bias_layer_3_p[i] 
        //         for (int j = 0; j < size_layer_3; j++)
        //         {
        //             weights_layer_3[i][j] = weights_layer_3_p[i][j];
        //         }
        //     }
            
        //     for (int i = 0; i < size_layer_3; i++)
        //     {
        //         bias_layer_4[i] = bias_layer_4_p[i] 
        //         for (int j = 0; j < size_layer_4; j++)
        //         {
        //             weights_layer_4[i][j] = weights_layer_4_p[i][j];
        //         }
        //     }
            
        //    for (int i = 0; i < size_layer_4; i++)
        //     {
        //         bias_output[i] = bias_output_p[i] 
        //         for (int j = 0; j < output_size; j++)
        //         {
        //             weights_output[i][j] = weights_output_p[i][j];
        //         }
        //     }
            

        }

        void updata_weights_bias(int weights_layer_1_p[][], int bias_layer_1_p[], int weights_layer_2_p[][], int bias_layer_2_p[],
                                 int weights_layer_3_p[][], int bias_layer_3_p[], int weights_layer_4_p[][], int bias_layer_4_p[],
                                 int weights_output_p[][], int bias_output_p[] ){
            copy_bias_weights(weights_layer_1, bias_layer_1, weights_layer_1_p, bias_layer_1_p);
            copy_bias_weights(weights_layer_2, bias_layer_2, weights_layer_2_p, bias_layer_2_p);
            copy_bias_weights(weights_layer_3, bias_layer_3, weights_layer_3_p, bias_layer_3_p);
            copy_bias_weights(weights_layer_4, bias_layer_4, weights_layer_4_p, bias_layer_4_p);
            copy_bias_weights(weights_output, bias_output,  weights_output_p, bias_output_p);        
        }

        int *calculate_out_put(int input[]){
            int layer1[] = calculate_w_b_i(weights_layer_1, bias_layer_1, input,  input_size   , size_layer_1 );
            int layer2[] = calculate_w_b_i(weights_layer_2, bias_layer_2, layer1, size_layer_1 , size_layer_2 );
            int layer3[] = calculate_w_b_i(weights_layer_3, bias_layer_3, layer2, size_layer_2 , size_layer_3 );
            int layer4[] = calculate_w_b_i(weights_layer_4, bias_layer_4, layer3, size_layer_3 , size_layer_4 );
            int out[]    = calculate_w_b_i(weights_output, bias_output, layer4,   size_layer_4 , output_size );

            return out;
        }

        int *calculate_out_put_relu(int input[]){
            int layer1[] = calculate_w_b_i(weights_layer_1, bias_layer_1, input,  input_size   , size_layer_1 );
            int layer2[] = calculate_w_b_i(weights_layer_2, bias_layer_2, layer1, size_layer_1 , size_layer_2 );
            int layer3[] = calculate_w_b_i(weights_layer_3, bias_layer_3, layer2, size_layer_2 , size_layer_3 );
            int layer4[] = calculate_w_b_i(weights_layer_4, bias_layer_4, layer3, size_layer_3 , size_layer_4 );
            int out[]    = calculate_w_b_i(weights_output, bias_output, layer4,   size_layer_4 , output_size );

            return out;
        }


        int define_direction_to_move(int input[]){
            int out[] = calculate_out_put(input);
            int max = -1
            int direction_to_move = 0;
            for (int i = 0; i < output_size; i++)
            {
                if (max < out[i])
                {
                    max = out[i];
                    direction_to_move = i;
                }
            }
            return direction_to_move;
        }
        
};




int main(int argc, char const *argv[])
{
    
    return 0;
}


