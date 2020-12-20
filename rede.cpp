#include <bits/stdc++.h>
#define debug(x) cout << #x << " : " << x << endl;
#define input_size 10000
#define size_layer_1 100
#define size_layer_2 100
#define size_layer_3 100
#define size_layer_4 100
#define output_size 8

typedef float layType; 

using namespace std;

class rede
{
    private:
        void copy_bias_weights(layType **weights_layer, layType *bias_layer,
                               layType **weights_layer_p, layType *bias_layer_p){
            for (int i = 0; i < input_size; i++)
            {
                bias_layer[i] = bias_layer_p[i];
                for (int j = 0; j < size_layer_1; j++)
                {
                    weights_layer[i][j] = weights_layer_p[i][j];
                }
            }
        }

        layType **alloca_matrix(int lin, int col){
            layType ** mat = (layType **)malloc(sizeof(layType *) * lin);
            for (int i = 0; i < col; i++)
            {
                mat[i] = (layType *)malloc(sizeof(layType) * col);
            }
            return mat;
        }
        
        layType *alloca_array(int n){
            layType * array = (layType *)malloc(sizeof(int) * n);
            return array;
        }
        void free_matrix(layType ***mat,int lin){
            for (int i = 0; i < lin; i++)
            {
                free(*mat[i]);
            }
            
            free(*mat);
        }

        

        layType sigmoid(int x){
            return x / (1 + abs(x));
        }

        layType *calculate_w_b_i(layType **weights_layer, layType *bias_layer,
                             layType *inp_lay, int lin, int col){
            /*
                lin - numero de linhas da matriz
                col - numero de colunas da matriz
                weights_layer - matriz de layers (lin x col)
                inp_lay - layer de input (col x 1)
                bias_layer - matriz de bias (lin x 1)

                return ((weights_layer x inp_lay) + bias_layer) 
                dimensions (lin x 1)  
            */

            layType out_lay[lin];
            memset(out_lay, 0, lin * sizeof(layType));
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
        layType **weights_layer_1;
        layType *bias_layer_1;

        layType **weights_layer_2;
        layType *bias_layer_2;

        layType **weights_layer_3;
        layType *bias_layer_3;

        layType **weights_layer_4;
        layType *bias_layer_4;

        layType **weights_output;
        layType *bias_output;
        

        rede(layType **weights_layer_1_p,layType *bias_layer_1_p,layType **weights_layer_2_p,layType *bias_layer_2_p,
             layType **weights_layer_3_p,layType *bias_layer_3_p,layType **weights_layer_4_p,layType *bias_layer_4_p,
             layType **weights_output_p,layType *bias_output_p ){
            
            weights_layer_1 = alloca_matrix(input_size,size_layer_1);
            bias_layer_1 = alloca_array(size_layer_1);

            weights_layer_2 = alloca_matrix(size_layer_1,size_layer_2);
            bias_layer_2 = alloca_array(size_layer_2);

            weights_layer_3 = alloca_matrix(size_layer_2,size_layer_3);
            bias_layer_3 = alloca_array(size_layer_3);

            weights_layer_4 = alloca_matrix(size_layer_3,size_layer_4);
            bias_layer_4 = alloca_array(size_layer_4);

            weights_output = alloca_matrix(size_layer_4,output_size);
            bias_output = alloca_array(output_size);


            copy_bias_weights(weights_layer_1, bias_layer_1, weights_layer_1_p, bias_layer_1_p);
            copy_bias_weights(weights_layer_2, bias_layer_2, weights_layer_2_p, bias_layer_2_p);
            copy_bias_weights(weights_layer_3, bias_layer_3, weights_layer_3_p, bias_layer_3_p);
            copy_bias_weights(weights_layer_4, bias_layer_4, weights_layer_4_p, bias_layer_4_p);
            copy_bias_weights(weights_output, bias_output, weights_output_p, bias_output_p);


        }

        void updata_weights_bias(layType **weights_layer_1_p, layType *bias_layer_1_p, layType **weights_layer_2_p, layType *bias_layer_2_p,
                                 layType **weights_layer_3_p, layType *bias_layer_3_p, layType **weights_layer_4_p, layType *bias_layer_4_p,
                                 layType **weights_output_p, layType *bias_output_p ){
            copy_bias_weights(weights_layer_1, bias_layer_1, weights_layer_1_p, bias_layer_1_p);
            copy_bias_weights(weights_layer_2, bias_layer_2, weights_layer_2_p, bias_layer_2_p);
            copy_bias_weights(weights_layer_3, bias_layer_3, weights_layer_3_p, bias_layer_3_p);
            copy_bias_weights(weights_layer_4, bias_layer_4, weights_layer_4_p, bias_layer_4_p);
            copy_bias_weights(weights_output, bias_output,  weights_output_p, bias_output_p);        
        }

        layType *calculate_out_put(layType *input){
            layType *layer1 = calculate_w_b_i(weights_layer_1, bias_layer_1, input,  input_size   , size_layer_1 );
            layType *layer2 = calculate_w_b_i(weights_layer_2, bias_layer_2, layer1, size_layer_1 , size_layer_2 );
            layType *layer3 = calculate_w_b_i(weights_layer_3, bias_layer_3, layer2, size_layer_2 , size_layer_3 );
            layType *layer4 = calculate_w_b_i(weights_layer_4, bias_layer_4, layer3, size_layer_3 , size_layer_4 );
            layType *out    = calculate_w_b_i(weights_output, bias_output, layer4,   size_layer_4 , output_size );

            return out;
        }

        layType *calculate_out_put_relu(layType *input){
            layType *layer1 = calculate_w_b_i(weights_layer_1, bias_layer_1, input,  input_size   , size_layer_1 );
            layType *layer2 = calculate_w_b_i(weights_layer_2, bias_layer_2, layer1, size_layer_1 , size_layer_2 );
            layType *layer3 = calculate_w_b_i(weights_layer_3, bias_layer_3, layer2, size_layer_2 , size_layer_3 );
            layType *layer4 = calculate_w_b_i(weights_layer_4, bias_layer_4, layer3, size_layer_3 , size_layer_4 );
            layType *out    = calculate_w_b_i(weights_output, bias_output, layer4,   size_layer_4 , output_size );

            return out;
        }


        int define_direction_to_move(layType *input){
            layType *out = calculate_out_put(input);
            layType max = -1;
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
        
        void free_all_layers(){
            free_matrix(&weights_layer_1, input_size);
            free_matrix(&weights_layer_2, size_layer_1);
            free_matrix(&weights_layer_3, size_layer_2);
            free_matrix(&weights_layer_4, size_layer_3);
            free_matrix(&weights_output,  size_layer_4);

            free(bias_layer_1);
            free(bias_layer_2);
            free(bias_layer_3);
            free(bias_layer_4);
            free(bias_output);
        }

        float RandomFloat(float a, float b) {
            float random = ((float) rand()) / (float) RAND_MAX;
            float diff = b - a;
            float r = random * diff;
            return a + r;
        }

        /* se for atualizar o layType para int precisa modificar esse random Float para um random int msm */
        void update_bias_weights(layType ***mat, layType **array, int lin, int col, layType weights_range, layType bias_range){
            for (int i = 0; i < lin; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    (*mat[i][j]) +=  RandomFloat(0, weights_range);
                }
                (*array[i]) += RandomFloat(0, bias_range);
            }
            
        }

        void update_weights_and_bias_layer(layType weights_range, layType bias_range, int layer_to_change){
            switch (layer_to_change)
            {
            case 1:
                update_bias_weights(&weights_layer_1, &bias_layer_1, input_size, size_layer_1, weights_range, bias_range);
                break;
            case 2:
                update_bias_weights(&weights_layer_2, &bias_layer_2, size_layer_1, size_layer_2, weights_range, bias_range);
                break;
            case 3:
                update_bias_weights(&weights_layer_3, &bias_layer_3, size_layer_2, size_layer_3, weights_range, bias_range);
                break;
            case 4:
                update_bias_weights(&weights_layer_4, &bias_layer_4, size_layer_3, size_layer_4, weights_range, bias_range);
                break;
            case 5:
                update_bias_weights(&weights_output, &bias_output, size_layer_4, output_size, weights_range, bias_range);
                break;
            }
        }
};




int main(int argc, char const *argv[])
{

    

    
    return 0;
}


