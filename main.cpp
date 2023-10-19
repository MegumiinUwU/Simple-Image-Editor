
/* Project : Simple Image Editor
 * Purpose : Provide basic image filters to apply on .bmp images
 * Date    : 19 October 2023
 * Version : 2.0
 */

// Special thanks for our Prof. Mohamed El-Ramly

// Please make sure all images are .bmp and 256*256 pixels
// We tried our best to make our code easily read by humans the names of functions, variables all have meaning <3



#include <bits/stdc++.h>
#include <unistd.h>
#include "bmplib.cpp"
#include "bmplib.h"
#define ll long long
using namespace std;

// GIMAGE for gray images
// CIMAGE for colored images
unsigned char GIMAGE1 [SIZE][SIZE], GIMAGE2 [SIZE][SIZE];
unsigned char CIMAGE1 [SIZE][SIZE][RGB], CIMAGE2 [SIZE][SIZE][RGB];
int colored = 0; // Variable for determining if image is colored or not

// Kernels for sharpening the image
int kernel[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}};
int kernel2[3][3] ={
        {-1, -1, -1},
        {-1,  9, -1},
        {-1, -1, -1}};

// Kernels for edge detection
int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};
int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}};




// Function to read the image
void loadimage ()
{
    char imagename[1000], path[1000] = "\\To be transformed\\", cwd[1000] ;
    cout << "Please put all the images you want to apply filters on in 'To be transformed' directory " << '\n';
    cout << "Make sure all images are .bmp format and 256*256 pixels" << '\n';
    cout << "please enter the image name only " << '\n';
    cin  >> imagename;
    strcat(imagename,".bmp");
    strcat(path,imagename);
    cout << "Is the image colored or gray?" << '\n' << "1. Gray" << '\n' << "2. Colored" << '\n';
    cin  >> colored;
    if ( colored == 1 )
    {
        readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path), GIMAGE1);
    }
    if ( colored == 2 )
    {
        readRGBBMP(strcat(getcwd(cwd, sizeof(cwd)), path), CIMAGE1);
    }
}


// Function to save the image
void saveimage ()
{
    char imagename[1000], path[1000] = "\\Transformed\\", cwd[1000] ;
    cout << "Please name your new image" << '\n';
    cin  >> imagename;
    strcat (imagename, ".bmp");
    strcat(path,imagename);
    if ( colored == 1 )
    {
        writeGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path), GIMAGE1);
    }
    if ( colored == 2 )
    {
        writeRGBBMP(strcat(getcwd(cwd, sizeof(cwd)), path), CIMAGE1);
    }
    cout << "Image saved in " << strcat(getcwd(cwd, sizeof(cwd)), path) << '\n';
}

// Function to read a second image for the merge case
void load_for_merge ()
{
    cout << "You picked the merge filter please follow the steps below " << '\n';
    char imagename[1000], path[1000] = "\\To be transformed\\", cwd[1000] ;
    cout << "Please enter the name only for the second image " << '\n';
    cin  >> imagename;
    strcat(imagename,".bmp");
    strcat(path,imagename);
    if ( colored == 1 )
    {
        readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path), GIMAGE2);
    }
    if ( colored == 2 )
    {
        readRGBBMP(strcat(getcwd(cwd, sizeof(cwd)), path), CIMAGE2);
    }
}

// The merge filter
void toMerge ()
{
    load_for_merge();
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = ( ( GIMAGE1[i][j] + GIMAGE2[i][j] ) / 2 );
            }
        }
    }
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = ( ( CIMAGE1[i][j][k] + CIMAGE2[i][j][k] ) / 2 )  ;
                }
            }
        }
    }

}

// Function to adjust the brightness of images
void Brightness_adjust ()
{
    int options;
    cout << "You picked Darken or Lighten Image" << '\n';
    cout << "1. To increase brightness" << '\n' << "2. To decrease brightness" << '\n';
    cin >> options;
    if ( options == 1 )
    {
        if ( colored == 1 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    int tmp; //temporay variable
                    tmp = ( ( GIMAGE1[i][j] * 0.5 ) + GIMAGE1[i][j] ) ;
                    if ( tmp >= 255 )
                    {
                        GIMAGE1[i][j] = 255;
                    }
                    else
                    {
                        GIMAGE1[i][j] = ( ( GIMAGE1[i][j] * 0.5 ) + GIMAGE1[i][j] ) ;
                    }
                }
            }
        }
        if ( colored == 2 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    for (int k = 0; k < RGB; ++k)
                    {
                        int tmp;
                        tmp = (  CIMAGE1[i][j][k] * 1.5 );
                        if ( tmp >= 255 )
                        {
                            CIMAGE1[i][j][k] = 255 ;
                        }
                        else
                        {
                            CIMAGE1[i][j][k] = (  CIMAGE1[i][j][k] * 1.5 );
                        }
                    }
                }
            }
        }
    }
    if ( options == 2 )
    {
        if ( colored == 1 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    int tmp;
                    tmp = ( GIMAGE1[i][j] - ( GIMAGE1[i][j] * 0.5 ) ) ;
                    if ( tmp <= 0 )
                    {
                        GIMAGE1[i][j] = 0;
                    }
                    else
                    {
                        GIMAGE1[i][j] = ( GIMAGE1[i][j] - ( GIMAGE1[i][j] * 0.5 ) ) ;
                    }

                }
            }
        }
        if ( colored == 2 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    for (int k = 0; k < RGB; ++k)
                    {
                        int tmp;
                        tmp = (  CIMAGE1[i][j][k] / 1.5 ) ;
                        if ( tmp <= 0 )
                        {
                            CIMAGE1[i][j][k] = 0;
                        }
                        else
                        {
                            CIMAGE1[i][j][k] = (  CIMAGE1[i][j][k] / 1.5 );
                        }

                    }
                }
            }
        }

    }
}

// Function to turn RGB image to Gray scale
void Colored_to_Gray ()
{
    cout << "You picked colored to gray scale filter" << '\n';
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int average = 0;
            for (int k = 0; k < RGB; ++k)
            {
                average += CIMAGE1[i][j][k];

            }
            int tmp = average / 3;
            CIMAGE1[i][j][0] = tmp;
            CIMAGE1[i][j][1] = tmp;
            CIMAGE1[i][j][2] = tmp;
        }

    }
}

// Function to turn an image to Black and white
void Black_White ()
{
    cout << "You picked Black and white filter" << '\n' ;
    if ( colored == 1 )
    {
        int average = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                average += GIMAGE1[i][j];
            }
        }
        int tmp = ( average / 65536 );
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if ( GIMAGE1[i][j] >= tmp )
                {
                    GIMAGE1[i][j] = 255 ;
                }
                else
                {
                    GIMAGE1[i][j] = 0 ;
                }

            }

        }
    }
    if ( colored == 2 )
    {
        int GrayAverage = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                int average = 0;
                for (int k = 0; k < RGB; ++k)
                {
                    average += CIMAGE1[i][j][k];

                }
                GrayAverage += ( average / 3 );
                CIMAGE1[i][j][0] = ( average / 3 );
                CIMAGE1[i][j][1] = ( average / 3 );
                CIMAGE1[i][j][2] = ( average / 3 );

            }

        }
        int tmp = ( GrayAverage / 65536 );
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {


                    if ( CIMAGE1[i][j][0] >= tmp )
                    {
                        CIMAGE1[i][j][0] = 255;
                        CIMAGE1[i][j][1] = 255;
                        CIMAGE1[i][j][2] = 255;

                    }
                    else
                    {
                        CIMAGE1[i][j][0] = 0;
                        CIMAGE1[i][j][1] = 0;
                        CIMAGE1[i][j][2] = 0;
                    }


            }

        }

    }
}

// Function to Invert image colors
void Invert_Color ()
{
    cout << "You picked to invert colors of the image" << '\n';
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = ( 255 - GIMAGE1[i][j] );

            }

        }
    }
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = ( 255 - CIMAGE1[i][j][k] );

                }

            }

        }

    }
}

// Function to rotate images by 90 degrees
void rotate_90_degree ()
{
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = SIZE - 1; j >= 0; --j)
            {
                GIMAGE2 [i][(SIZE-1)-j] = GIMAGE1[j][i];

            }

        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }

    }
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = SIZE - 1; j >= 0; --j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE2 [i][(SIZE-1)-j][k] = CIMAGE1[j][i][k];

                }
            }

        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];

                }

            }
        }
    }

}


// Function to Flip an image
void Flip_Image ()
{
    int fliper;
    cout << "You picked flip image" << '\n' ;
    cout << "1. Flip horizontally" << '\n' << "2. Flip vertically" << '\n' ;
    cin >> fliper;
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = SIZE-1; j >=0 ; --j)
            {
                GIMAGE2[i][j] = GIMAGE1[i][(SIZE-1)-j];

            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }
        if ( fliper == 2 )
        {
            rotate_90_degree();
            rotate_90_degree();
        }
    }
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = SIZE-1; j >=0 ; --j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE2[i][j][k] = CIMAGE1[i][(SIZE-1)-j][k];
                }


            }
        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];

                }

            }
        }
        if ( fliper == 2 )
        {
            rotate_90_degree();
            rotate_90_degree();
        }



    }


}

// Function to rotate an image
void Rotate_Image ()
{
    int options;
    cout << "You picked rotate image" << '\n';
    cout << "1. Rotate by 90 degrees" << '\n' << "2. Rotate by 180 degrees" << '\n' << "3. Rotate by 270 degrees" << '\n';
    cin >> options;
    if ( options == 1 )
    {
        rotate_90_degree();
    }
    if ( options == 2 )
    {
        rotate_90_degree();
        rotate_90_degree();
    }
    if ( options == 3 )
    {
        rotate_90_degree();
        rotate_90_degree();
        rotate_90_degree();
    }
}

// Function to apply Mean Blur algorithm
void Mean_Blur ()
{
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                int average = 0 ;


                    if ( i > 0 && j > 0 && i < SIZE-1 && j < SIZE-1)
                    {
                        average += (GIMAGE1[i-1][j]);  //pixel above center
                        average += (GIMAGE1[i+1][j]);  //pixel below center
                        average += (GIMAGE1[i][j+1]);  //pixel on the right of center
                        average += (GIMAGE1[i][j-1]);  //pixel on the left of center

                        // upper edges
                        average += (GIMAGE1[i-1][j-1]);
                        average += (GIMAGE1[i-1][j+1]);

                        // lower edges
                        average += (GIMAGE1[i+1][j-1]);
                        average += (GIMAGE1[i+1][j+1]);
                        // the center
                        average += (GIMAGE1[i][j]);

                        average = ( average / 9 );


                    }
                    else if ( i == 0 && j < SIZE-1)
                    {
                        average += (GIMAGE1[i+1][j]);
                        average += (GIMAGE1[i+1][j+1]);
                        average += (GIMAGE1[i][j+1]);
                        average += (GIMAGE1[i][j]);
                        average = ( average / 4);
                    }
                    else if (i == 0 && j == SIZE-1)
                    {
                        average += (GIMAGE1[i+1][j]);
                        average += (GIMAGE1[i+1][j-1]);
                        average += (GIMAGE1[i][j-1]);
                        average += (GIMAGE1[i][j]);
                        average = ( average / 4);

                    }
                    else if ( i == SIZE-1 && j < SIZE-1)
                    {
                        average += (GIMAGE1[i-1][j]);
                        average += (GIMAGE1[i-1][j+1]);
                        average += (GIMAGE1[i][j+1]);
                        average += (GIMAGE1[i][j]);
                        average = ( average / 4);
                    }
                    else if ( i == SIZE-1 && j == SIZE-1)
                    {
                        average += (GIMAGE1[i-1][j]);
                        average += (GIMAGE1[i-1][j-1]);
                        average += (GIMAGE1[i][j-1]);
                        average += (GIMAGE1[i][j]);
                        average = ( average / 4);
                    }
                    else
                    {
                        average += (GIMAGE1[i-1][j]);
                        average += (GIMAGE1[i-1][j-1]);
                        average += (GIMAGE1[i+1][j]);
                        average += (GIMAGE1[i][j]);
                        average = ( average / 4);
                    }




                GIMAGE2[i][j] = average;

            }


        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }

    }
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                int average1 = 0, average2 = 0, average3 =0; // Averages of R and G and B

                if ( i > 0 && j > 0 && i < SIZE-1 && j < SIZE-1)
                {
                    average1 += (CIMAGE1[i-1][j][0]);  //pixel above center
                    average2 += (CIMAGE1[i-1][j][1]);  //pixel above center
                    average3 += (CIMAGE1[i-1][j][2]);  //pixel above center

                    average1 += (CIMAGE1[i+1][j][0]);  //pixel below center
                    average2 += (CIMAGE1[i+1][j][1]);  //pixel below center
                    average3 += (CIMAGE1[i+1][j][2]);  //pixel below center

                    average1 += (CIMAGE1[i][j+1][0]);  //pixel on the right of center
                    average2 += (CIMAGE1[i][j+1][1]);  //pixel on the right of center
                    average3 += (CIMAGE1[i][j+1][2]);  //pixel on the right of center

                    average1 += (CIMAGE1[i][j-1][0]);  //pixel on the left of center
                    average2 += (CIMAGE1[i][j-1][1]);  //pixel on the left of center
                    average3 += (CIMAGE1[i][j-1][2]);  //pixel on the left of center

                    // upper edges
                    average1 += (CIMAGE1[i-1][j-1][0]);
                    average2 += (CIMAGE1[i-1][j-1][1]);
                    average3 += (CIMAGE1[i-1][j-1][2]);

                    average1 += (CIMAGE1[i-1][j+1][0]);
                    average2 += (CIMAGE1[i-1][j+1][1]);
                    average3 += (CIMAGE1[i-1][j+1][2]);

                    // lower edges
                    average1 += (CIMAGE1[i+1][j-1][0]);
                    average2 += (CIMAGE1[i+1][j-1][1]);
                    average3 += (CIMAGE1[i+1][j-1][2]);

                    average1 += (CIMAGE1[i+1][j+1][0]);
                    average2 += (CIMAGE1[i+1][j+1][1]);
                    average3 += (CIMAGE1[i+1][j+1][2]);

                    // the center
                    average1 += (CIMAGE1[i][j][0]);
                    average2 += (CIMAGE1[i][j][1]);
                    average3 += (CIMAGE1[i][j][2]);

                    average1 = ( average1 / 9 );
                    average2 = ( average2 / 9 );
                    average3 = ( average3 / 9 );

                }
                else if ( i == 0 && j < SIZE-1)
                {
                    average1 += (CIMAGE1[i+1][j][0]);
                    average2 += (CIMAGE1[i+1][j][1]);
                    average3 += (CIMAGE1[i+1][j][2]);

                    average1 += (CIMAGE1[i+1][j+1][0]);
                    average2 += (CIMAGE1[i+1][j+1][1]);
                    average3 += (CIMAGE1[i+1][j+1][2]);

                    average1 += (CIMAGE1[i][j+1][0]);
                    average2 += (CIMAGE1[i][j+1][1]);
                    average3 += (CIMAGE1[i][j+1][2]);

                    average1 += (CIMAGE1[i][j][0]);
                    average2 += (CIMAGE1[i][j][1]);
                    average3 += (CIMAGE1[i][j][2]);

                    average1 = ( average1 / 4);
                    average2 = ( average2 / 4);
                    average3 = ( average3 / 4);
                }
                else if (i == 0 && j == SIZE-1)
                {
                    average1 += (CIMAGE1[i+1][j][0]);
                    average2 += (CIMAGE1[i+1][j][1]);
                    average3 += (CIMAGE1[i+1][j][2]);

                    average1 += (CIMAGE1[i+1][j-1][0]);
                    average2 += (CIMAGE1[i+1][j-1][1]);
                    average3 += (CIMAGE1[i+1][j-1][2]);

                    average1 += (CIMAGE1[i][j-1][0]);
                    average2 += (CIMAGE1[i][j-1][1]);
                    average3 += (CIMAGE1[i][j-1][2]);

                    average1 += (CIMAGE1[i][j][0]);
                    average2 += (CIMAGE1[i][j][1]);
                    average3 += (CIMAGE1[i][j][2]);

                    average1 = ( average1 / 4);
                    average2 = ( average2 / 4);
                    average3 = ( average3 / 4);
                }
                else if ( i == SIZE-1 && j < SIZE-1)
                {
                    average1 += (CIMAGE1[i-1][j][0]);
                    average2 += (CIMAGE1[i-1][j][1]);
                    average3 += (CIMAGE1[i-1][j][2]);

                    average1 += (CIMAGE1[i-1][j+1][0]);
                    average2 += (CIMAGE1[i-1][j+1][1]);
                    average3 += (CIMAGE1[i-1][j+1][2]);

                    average1 += (CIMAGE1[i][j+1][0]);
                    average2 += (CIMAGE1[i][j+1][1]);
                    average3 += (CIMAGE1[i][j+1][2]);

                    average1 += (CIMAGE1[i][j][0]);
                    average2 += (CIMAGE1[i][j][1]);
                    average3 += (CIMAGE1[i][j][2]);

                    average1 = ( average1 / 4);
                    average2 = ( average2 / 4);
                    average3 = ( average3 / 4);
                }
                else if ( i == SIZE-1 && j == SIZE-1)
                {
                    average1 += (CIMAGE1[i-1][j][0]);
                    average2 += (CIMAGE1[i-1][j][1]);
                    average3 += (CIMAGE1[i-1][j][2]);

                    average1 += (CIMAGE1[i-1][j-1][0]);
                    average2 += (CIMAGE1[i-1][j-1][1]);
                    average3 += (CIMAGE1[i-1][j-1][2]);

                    average1 += (CIMAGE1[i][j-1][0]);
                    average2 += (CIMAGE1[i][j-1][1]);
                    average3 += (CIMAGE1[i][j-1][2]);

                    average1 += (CIMAGE1[i][j][0]);
                    average2 += (CIMAGE1[i][j][1]);
                    average3 += (CIMAGE1[i][j][2]);

                    average1 = ( average1 / 4);
                    average2 = ( average2 / 4);
                    average3 = ( average3 / 4);
                }
                else
                {
                    average1 += (CIMAGE1[i-1][j][0]);
                    average2 += (CIMAGE1[i-1][j][1]);
                    average3 += (CIMAGE1[i-1][j][2]);

                    average1 += (CIMAGE1[i-1][j-1][0]);
                    average2 += (CIMAGE1[i-1][j-1][1]);
                    average3 += (CIMAGE1[i-1][j-1][2]);

                    average1 += (CIMAGE1[i+1][j][0]);
                    average2 += (CIMAGE1[i+1][j][1]);
                    average3 += (CIMAGE1[i+1][j][2]);

                    average1 += (CIMAGE1[i][j][0]);
                    average2 += (CIMAGE1[i][j][1]);
                    average3 += (CIMAGE1[i][j][2]);

                    average1 = ( average1 / 4);
                    average2 = ( average2 / 4);
                    average3 = ( average3 / 4);
                }

                CIMAGE2[i][j][0] = average1;
                CIMAGE2[i][j][1] = average2;
                CIMAGE2[i][j][2] = average3;
            }


        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];

                }

            }
        }
    }

}

// Function to apply Gaussian Blur
void Gaussian_Blur ()
{
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                int average = 0 ;

                // 7x7 convolution


                    for (int k = i - 3; k < i + 4; ++k)
                    {
                        for (int l = j - 3; l < j + 4; ++l)
                        {
                            average += ( GIMAGE1[k][l] / 49 ) ;
                        }
                    }

                    GIMAGE2[i][j] = average ;


            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }
    }

    if ( colored == 2 )
    {

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                    // 7x7x3 convolution
                    int average1 = 0, average2 = 0, average3 = 0;
                    for (int yy = i - 3; yy < i + 4; ++yy)
                    {
                        for (int l = j - 3; l < j + 4; ++l)
                        {
                            average1 += ( CIMAGE1[yy][l][0] / 49 ) ;
                            average2 += ( CIMAGE1[yy][l][1] / 49 ) ;
                            average3 += ( CIMAGE1[yy][l][2] / 49 ) ;
                        }
                    }
                    CIMAGE2[i][j][0] = average1;
                    CIMAGE2[i][j][1] = average2;
                    CIMAGE2[i][j][2] = average3;

            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
                }


            }
        }
    }


}

// Display types of blur
void Blur_Menue ()
{
    int options;
    cout << "You picked Blur Image please choose blur type" << '\n'
         << "1. Low Mean Blur" << '\n'
         << "2. High Mean Blur" << '\n'
         << "3. Gaussian Blur" << '\n';
    cin >> options;
    if ( options == 1 )
    {
        for (int i = 0; i < 5; ++i)
        {
            Mean_Blur();
        }
    }
    if ( options == 2 )
    {
        for (int i = 0; i < 7; ++i)
        {
            Mean_Blur();

        }
    }
    if ( options == 3 )
    {
        Gaussian_Blur();
    }

}

void enlarge_first_quarter()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE2[i][j] = GIMAGE1[i/2][j/2];
        }

    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE1[i][j] = GIMAGE2[i][j];

        }
    }
}

// Function for enlarging image
void Enlarge_Image ()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE2[i][j] = 255;
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE2[i][j][k] = 255;

            }

        }

    }
    int options;
    cout << "Please pick enlarged quarter" << '\n'
         << "1 | 2" << '\n' << "3 | 4" << '\n';
    cin >> options;

    if ( colored == 1 )
    {
        if ( options == 1 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    GIMAGE2[i][j] = GIMAGE1[i/2][j/2];

                }
            }
        }
        if ( options == 2 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    GIMAGE2[i][j] = GIMAGE1[i/2][j/2 + 127];

                }
            }
        }
        if ( options == 3 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    GIMAGE2[i][j] = GIMAGE1[i/2 + 127][j/2];

                }


            }

        }
        if ( options == 4 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    GIMAGE2[i][j] = GIMAGE1[i/2 + 127][j/2 +127];

                }


            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }


    }
    if ( colored == 2 )
    {
        if ( options == 1 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    for (int k = 0; k < RGB; ++k)
                    {
                        CIMAGE2[i][j][k] = CIMAGE1[i/2][j/2][k];
                    }


                }
            }
        }
        if ( options == 2 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    for (int k = 0; k < RGB; ++k)
                    {
                        CIMAGE2[i][j][k] = CIMAGE1[i/2][j/2 +127][k];
                    }


                }
            }

        }
        if ( options == 3 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    for (int k = 0; k < RGB; ++k)
                    {
                        CIMAGE2[i][j][k] = CIMAGE1[i/2 +127][j/2][k];
                    }


                }
            }

        }
        if ( options == 4 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    for (int k = 0; k < RGB; ++k)
                    {
                        CIMAGE2[i][j][k] = CIMAGE1[i/2 +127][j/2 +127][k];
                    }


                }
            }
        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
                }


            }
        }

    }

}

// Make the Image sharper
void applySharpnessFilter()
{
    if ( colored == 1 )
    {
        for (int i = 1; i < SIZE - 1; ++i)
        {
            for (int j = 1; j < SIZE - 1; ++j)
            {
                int sum = 0;
                for (int k = -1; k <= 1; ++k)
                {
                    for (int kx = -1; kx <= 1; ++kx)
                    {
                        sum += kernel[k + 1][kx + 1] * GIMAGE1[i + k][j + kx];
                    }
                }
                GIMAGE2[i][j] = min(max(sum, 0), 255);  // Clipping to [0, 255]
            }
        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }
    }
    if ( colored == 2 )
    {
        for (int c = 0; c < RGB; c++) {
            for (int x = 1; x < SIZE - 1; x++) {
                for (int y = 1; y < SIZE - 1; y++) {
                    int sum = 0;

                    for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            sum += CIMAGE1[x + i][y + j][c] * kernel2[i + 1][j + 1];
                        }
                    }

                    // Clamp the result to the 0-255 range
                    CIMAGE2[x][y][c] = max(0, min(255, sum));
                }
            }
        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
                }


            }
        }


    }

}

// Function to detect edges by Sobel algorithm
void Detect_edges_Sobel ()
{
    for (int i = 0; i < SIZE ; ++i)
    {
        for (int j = 0; j < SIZE ; ++j)
        {
            GIMAGE2[i][j] = 0 ;
        }

    }
    if ( colored == 1 )
    {
        for (int i = 1; i < SIZE-1; ++i)
        {
            for (int j = 0; j < SIZE-1; ++j)
            {
                int sumX = 0, sumY = 0;
                int tmp1 = 0, tmp2 = 0;
                for (int k = i-1; k < i+1; ++k)
                {
                    for (int l = j-1; l < j+1; ++l)
                    {
                        sumX += ( GIMAGE1[k][l] * Gx[tmp1][tmp2]);
                        sumY += ( GIMAGE1[k][l] * Gy[tmp1][tmp2]);
                        tmp2++;

                    }
                    tmp1++;
                }
                int result = sqrt((sumX*sumX) + (sumY*sumY) );
                if ( result > 300 )
                {
                    GIMAGE2[i][j] = 0;
                }
                else
                {
                    GIMAGE2[i][j] = 255;
                }


            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }


    }

}

// Function to detect edges by comparison algorithm
void Detect_egdes_compare ()
{
    int type;
    cout << "1. Pencil " << '\n' << "2. Ink" << '\n';
    cin >> type;
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                int detector = 30;
                int pencil;
                if ( type == 1 )
                {
                    pencil = 95;
                }
                else
                {
                    pencil = 55;

                }
                if ( i > 0 && j > 0 && i < SIZE-1 && j < SIZE-1)
                {
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i+1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i-1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j+1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j-1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }

                }
                else if ( i == 0 && j < SIZE-1 && j > 0)
                {
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i+1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j+1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j-1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                }
                else if (i == 0 && j == SIZE-1)
                {
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i+1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j-1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }

                }
                else if ( i == SIZE-1 && j < SIZE-1 && j > 0)
                {
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i-1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j+1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j-1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }


                }
                else if ( i == SIZE-1 && j == SIZE-1)
                {
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i-1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j-1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }

                }
                else if ( i == 0 && j == 0 )
                {
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i+1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j+1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                }
                else if ( i == SIZE-1 && j == 0 )
                {
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i-1][j]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                    if ( ( abs(GIMAGE1[i][j] - GIMAGE1[i][j+1]) ) > detector )
                    {
                        GIMAGE2[i][j] = pencil;
                        continue;
                    }
                }

                GIMAGE2[i][j] = 255;

            }
        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }

    }
}

// Function to display edge detection menu
void Edge_menu ()
{
    if ( colored == 2 )
    {
        Colored_to_Gray();
        for (int i = 0; i < SIZE ; ++i)
        {
            for (int j = 0; j < SIZE ; ++j)
            {
                GIMAGE1[i][j] = CIMAGE1[i][j][0];

            }

        }

    }
    colored = 1;
    int options;
    cout << "You picked edge detection please choose the type" << '\n'
         << "1. Draw Detection" << '\n' << "2. Sobel Detection" << '\n';
    cin >> options;
    if ( options == 1 )
    {
        Detect_egdes_compare();
    }
    else
    {
        Detect_edges_Sobel();
    }


}

// Function to shrink images
void Shrink_image ()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE2[i][j] = 255;
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE2[i][j][k] = 255;

            }

        }
    }
    int options;
    cout << "You picked to shrink the image please choose the ratio" << '\n'
         << "1. Shrink to 1/2" << '\n' << "2. Shrink to 1/3" << '\n' << "3. Shrink to 1/4" << '\n';
    cin >> options;
    if ( colored == 1 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {

                if ( options == 1 && i * 2 <= 255 && j * 2 <= 255 )
                {
                    GIMAGE2[i][j] = GIMAGE1[i*2][j*2];
                }
                else if ( options == 2 && i * 3 <= 255 && j * 3 <= 255 )
                {
                    GIMAGE2[i][j] = GIMAGE1[i*3][j*3];
                }
                else if ( options == 3 && i * 4 <= 255 && j * 4 <= 255 )
                {
                    GIMAGE2[i][j] = GIMAGE1[i*4][j*4];
                }


            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];

            }
        }

    }
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {

                if ( options == 1 && i * 2 <= 255 && j * 2 <= 255 )
                {
                    CIMAGE2[i][j][0] = CIMAGE1[i*2][j*2][0];
                    CIMAGE2[i][j][1] = CIMAGE1[i*2][j*2][1];
                    CIMAGE2[i][j][2] = CIMAGE1[i*2][j*2][2];
                }
                else if ( options == 2 && i * 3 <= 255 && j * 3 <= 255 )
                {
                    CIMAGE2[i][j][0] = CIMAGE1[i*3][j*3][0];
                    CIMAGE2[i][j][1] = CIMAGE1[i*3][j*3][1];
                    CIMAGE2[i][j][2] = CIMAGE1[i*3][j*3][2];
                }
                else if ( options == 3 && i * 4 <= 255 && j * 4 <= 255 )
                {
                    CIMAGE2[i][j][0] = CIMAGE1[i*4][j*4][0];
                    CIMAGE2[i][j][1] = CIMAGE1[i*4][j*4][1];
                    CIMAGE2[i][j][2] = CIMAGE1[i*4][j*4][2];
                }


            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
                }


            }
        }

    }
}

// Function to Mirror image
void Mirror_Image()
{

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = SIZE-1; j >=0 ; --j)
        {
            GIMAGE2[i][j] = GIMAGE1[i][(SIZE-1)-j];

        }

    }
    cout << "You picked Mirror filter please choose mirror type" << '\n'
         << "1. Right Mirror" << '\n' << "2. Left Mirror" << '\n' << "3. Top Mirror" << '\n' << "4. Down Mirror" << '\n';
    int options;
    cin >> options;
    if ( colored == 1 )
    {
        if ( options == 1 )
        {
            for (int i = 0; i < SIZE ; ++i)
            {
                for (int j = 0; j < 128; ++j)
                {
                    GIMAGE1[i][j] = GIMAGE1[i][(SIZE-1)-j];

                }

            }

        }
        if ( options == 2 )
        {

            for (int i = 0; i < SIZE ; ++i)
            {
                for (int j = 127; j < SIZE; ++j)
                {
                    GIMAGE1[i][j] = GIMAGE2[i][j];

                }

            }
        }
        if ( options == 3)
        {
            for (int i = 0; i < 128 ; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    GIMAGE1[(SIZE-1)-i][j] = GIMAGE1[i][j];

                }

            }
        }
        if ( options == 4)
        {
            for (int i = 0; i < 128 ; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    GIMAGE1[i][j] = GIMAGE1[(SIZE-1)-i][j];

                }

            }
        }



    }
    if ( colored == 2 )
    {
        if ( options == 1 )
        {
            for (int i = 0; i < SIZE ; ++i)
            {
                for (int j = 0; j < 128; ++j)
                {
                    CIMAGE1[i][j][0] = CIMAGE1[i][(SIZE-1)-j][0];
                    CIMAGE1[i][j][1] = CIMAGE1[i][(SIZE-1)-j][1];
                    CIMAGE1[i][j][2] = CIMAGE1[i][(SIZE-1)-j][2];

                }

            }

        }
        if ( options == 2 )
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = SIZE-1; j >=0 ; --j)
                {
                    for (int k = 0; k < RGB; ++k)
                    {
                        CIMAGE2[i][j][k] = CIMAGE1[i][(SIZE-1)-j][k];
                    }


                }
            }
            for (int i = 0; i < SIZE ; ++i)
            {
                for (int j = 127; j < SIZE; ++j)
                {
                    CIMAGE1[i][j][0] = CIMAGE2[i][j][0];
                    CIMAGE1[i][j][1] = CIMAGE2[i][j][1];
                    CIMAGE1[i][j][2] = CIMAGE2[i][j][2];

                }

            }
        }
        if ( options == 3)
        {
            for (int i = 0; i < 128 ; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    CIMAGE1[(SIZE-1)-i][j][0] = CIMAGE1[i][j][0];
                    CIMAGE1[(SIZE-1)-i][j][1] = CIMAGE1[i][j][1];
                    CIMAGE1[(SIZE-1)-i][j][2] = CIMAGE1[i][j][2];

                }

            }
        }
        if ( options == 4)
        {
            for (int i = 0; i < 128 ; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    CIMAGE1[i][j][0] = CIMAGE1[(SIZE-1)-i][j][0];
                    CIMAGE1[i][j][1] = CIMAGE1[(SIZE-1)-i][j][1];
                    CIMAGE1[i][j][2] = CIMAGE1[(SIZE-1)-i][j][2];
                }

            }
        }



    }


}

// Function to crop an image
void Crop ()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE2[i][j] = 255;
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE2[i][j][k] = 255;

            }

        }
    }
    int x = 0, y = 0, w = 0, l = 0;
    cout << "You picked crop please enter x,y values for center of the remained" << '\n';
    cout << "X : ";
    cin >> x;
    cout << '\n' << "Y : ";
    cin >> y;
    cout << '\n' << "Now enter length and width of the remained square" << '\n' << "L : ";
    cin >> l;
    cout << '\n' << "W : ";
    cin >> w;
    cout << '\n';

    if ( colored == 1 )
    {
        for (int i = x; i < l + x ; ++i)
        {
            for (int j = y; j < w + y ; ++j)
            {
                GIMAGE2[i][j] = GIMAGE1[i][j];

            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];
            }

        }
    }
    if ( colored == 2 )
    {
        for (int i = x; i < l + x ; ++i)
        {
            for (int j = y; j < w + y ; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE2[i][j][k] = CIMAGE1[i][j][k];
                }


            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {

                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
                }

            }

        }
    }

}

// Function to make the image ready for ascii art
void Ascii_ready ()
{
    if ( colored == 2 )
    {
        Colored_to_Gray();
        for (int i = 0; i < SIZE ; ++i)
        {
            for (int j = 0; j < SIZE ; ++j)
            {
                GIMAGE1[i][j] = CIMAGE1[i][j][0];

            }

        }

    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {

            if (i * 5 <= 255 && j * 5 <= 255)
            {
                GIMAGE2[i][j] = GIMAGE1[i * 5][j * 5];
            }

        }
    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE1[i][j] = GIMAGE2[i][j];

        }
    }
}

// Function for Ascii art generator
void Ascii_art ()
{
    cout << "Welcome to Ascii Art generator" << '\n';
    Ascii_ready();
    ofstream MyFile("ASCIIART.txt");
    for (int i = 0; i < 54; ++i)
    {
        for (int j = 0; j < 54; ++j)
        {
            if ( GIMAGE1[i][j] < 120 )
            {
                MyFile << '.';
            }
            else
            {
                MyFile << " ";
            }


        }
        MyFile << '\n';

    }
    MyFile.close();


}

// Function for Greening the image
void Greenish_Image ()
{
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                CIMAGE1[i][j][0] = ( 0.299 * CIMAGE1[i][j][0] );
                CIMAGE1[i][j][1] = ( 0.587 * CIMAGE1[i][j][1] );
                CIMAGE1[i][j][2] = ( 0.114 * CIMAGE1[i][j][2] );

            }

        }
    }
    else
    {
        cout << "Sorry can't make this filter on gray images" << '\n';
    }

}

// Function needed in comparing 8 pixels in Cartoon filter
int findLargestAmong(int num1, int num2, int num3, int num4, int num5, int num6, int num7, int num8)
{
    int largest = num1;

    if (num2 > largest) {
        largest = num2;
    }
    if (num3 > largest) {
        largest = num3;
    }
    if (num4 > largest) {
        largest = num4;
    }
    if (num5 > largest) {
        largest = num5;
    }
    if (num6 > largest) {
        largest = num6;
    }
    if (num7 > largest) {
        largest = num7;
    }
    if (num8 > largest) {
        largest = num8;
    }


    return largest;
}
int findSmallestAmong(int num1, int num2, int num3, int num4, int num5, int num6, int num7, int num8)
{
    int smallest = num1;

    if (num2 < smallest) {
        smallest = num2;
    }
    if (num3 < smallest) {
        smallest = num3;
    }
    if (num4 < smallest) {
        smallest = num4;
    }
    if (num5 < smallest) {
        smallest = num5;
    }
    if (num6 < smallest) {
        smallest = num6;
    }
    if (num7 < smallest) {
        smallest = num7;
    }
    if (num8 < smallest) {
        smallest = num8;
    }

    return smallest;
}

// Blue filter Function
void Chanel_swap ()
{
    cout << "You picked Blue filter for colored images" << '\n';
    if ( colored == 2 )
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                CIMAGE2[i][j][0] = CIMAGE1[i][j][2];
                CIMAGE2[i][j][1] = CIMAGE1[i][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j][0];

            }

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < RGB; ++k)
                {
                    CIMAGE1[i][j][k] = CIMAGE2[i][j][k];

                }

            }

        }

    }
}
// Sepia filter Function
void Sepia ()
{
    cout << "You picked Sepia filter for colored images" << '\n';
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int x,y,z;
            x = (  0.393 * CIMAGE1[i][j][0] + 0.769 * CIMAGE1[i][j][1] + 0.189 * CIMAGE1[i][j][2] );
            y = (  0.349 * CIMAGE1[i][j][0] + 0.686 * CIMAGE1[i][j][1] + 0.168 * CIMAGE1[i][j][2] );
            z = (  0.272 * CIMAGE1[i][j][0] + 0.534 * CIMAGE1[i][j][1] + 0.131 * CIMAGE1[i][j][2]);
            if ( x > 255 )
            {
                CIMAGE2[i][j][0] = 255;
            }
            else
            {
                CIMAGE2[i][j][0] = x;
            }
            if ( y > 255 )
            {
                CIMAGE2[i][j][1] = 255;
            }
            else
            {
                CIMAGE2[i][j][1] = y;
            }
            if ( z > 255 )
            {
                CIMAGE2[i][j][2] = 255;
            }
            else
            {
                CIMAGE2[i][j][2] = z;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
            }
        }
    }
}

// Function for Orange filter
void Warm_tint_orange ()
{
    int tint_value = 50;
    cout << "You picked Warm filter for colored images" << '\n';
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int x,y;
            x = (  CIMAGE1[i][j][0] + tint_value );
            y = (  CIMAGE1[i][j][0] - tint_value );
            if ( x > 255 )
            {
                CIMAGE2[i][j][0] = 255;
            }
            else
            {
                CIMAGE2[i][j][0] = x;
            }
            if ( y > 255 )
            {
                CIMAGE2[i][j][1] = 255;
            }
            else if ( y < 0)
            {
                CIMAGE2[i][j][1] = 0;
            }
            else
            {
                CIMAGE2[i][j][1] = y;
            }
            CIMAGE2[i][j][2] = CIMAGE1[i][j][2] ;

        }
    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
            }
        }
    }
}

// Function for Ektachrome filter
void Ektachrome ()
{
    int tint_value = 30;
    cout << "You picked Ektachrome filter for colored images" << '\n';
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int x,y,z;
            x = (  CIMAGE1[i][j][0] + tint_value );
            y = (  CIMAGE1[i][j][1] + tint_value );
            z = (  CIMAGE1[i][j][2] - tint_value );
            if ( x > 255 )
            {
                CIMAGE2[i][j][0] = 255;
            }
            else
            {
                CIMAGE2[i][j][0] = x;
            }
            if ( y > 255 )
            {
                CIMAGE2[i][j][1] = 255;
            }
            else
            {
                CIMAGE2[i][j][1] = y;
            }
            if ( z > 255 )
            {
                CIMAGE2[i][j][2] = 255;
            }
            else if ( z < 0)
            {
                CIMAGE2[i][j][2] = 0;
            }
            else
            {
                CIMAGE2[i][j][2] = z ;
            }



        }
    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
            }
        }
    }
}

// Function for shuffle
void shuffle ()
{
    int options[4];
    cout << "Welcome to shuffle please insert the required shuffle order where each image has 4 quads " << '\n'
         << "1 | 2" << '\n' << "3 | 4" << '\n';
    for (int i = 0; i < 4; ++i)
    {
        cin >> options[i];
        if ( options[i] > 4 || options[i] < 1 )
        {
            cout << "This quad doesn't exist try again";
            return;
        }

    }
    // quad1 deciding
    for (int i = 0; i < 128; ++i)
    {
        for (int j = 0; j < 128; ++j)
        {
            if ( options[0] == 1 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j];
                CIMAGE2[i][j][0] = CIMAGE1[i][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j][2];
            }
            if ( options[0] == 2 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j+128];
                CIMAGE2[i][j][0] = CIMAGE1[i][j+128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j+128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j+128][2];
            }
            if ( options[0] == 3 )
            {
                GIMAGE2[i][j] = GIMAGE1[i+128][j];
                CIMAGE2[i][j][0] = CIMAGE1[i+128][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i+128][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i+128][j][2];
            }
            if ( options[0] == 4 )
            {
                GIMAGE2[i][j] = GIMAGE1[i+128][j+128];
                CIMAGE2[i][j][0] = CIMAGE1[i+128][j+128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i+128][j+128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i+128][j+128][2];
            }

        }

    }
    // quad2 deciding
    for (int i = 0; i < 128; ++i)
    {
        for (int j = 128; j < SIZE; ++j)
        {
            if ( options[1] == 1 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j-128];
                CIMAGE2[i][j][0] = CIMAGE1[i][j-128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j-128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j-128][2];
            }
            if ( options[1] == 2 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j];
                CIMAGE2[i][j][0] = CIMAGE1[i][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j][2];
            }
            if ( options[1] == 3 )
            {
                GIMAGE2[i][j] = GIMAGE1[i+128][j-128];
                CIMAGE2[i][j][0] = CIMAGE1[i+128][j-128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i+128][j-128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i+128][j-128][2];
            }
            if ( options[1] == 4 )
            {
                GIMAGE2[i][j] = GIMAGE1[i+128][j];
                CIMAGE2[i][j][0] = CIMAGE1[i+128][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i+128][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i+128][j][2];
            }

        }

    }
    // quad3 deciding
    for (int i = 128; i < SIZE; ++i)
    {
        for (int j = 0; j < 128; ++j)
        {
            if ( options[2] == 1 )
            {
                GIMAGE2[i][j] = GIMAGE1[i-128][j];
                CIMAGE2[i][j][0] = CIMAGE1[i-128][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i-128][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i-128][j][2];
            }
            if ( options[2] == 2 )
            {
                GIMAGE2[i][j] = GIMAGE1[i-128][j+128];
                CIMAGE2[i][j][0] = CIMAGE1[i-128][j+128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i-128][j+128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i-128][j+128][2];
            }
            if ( options[2] == 3 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j];
                CIMAGE2[i][j][0] = CIMAGE1[i][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j][2];
            }
            if ( options[2] == 4 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j+128];
                CIMAGE2[i][j][0] = CIMAGE1[i][j+128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j+128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j+128][2];
            }

        }

    }
    // quad4 deciding
    for (int i = 128; i < SIZE; ++i)
    {
        for (int j = 128; j < SIZE; ++j)
        {
            if ( options[3] == 1 )
            {
                GIMAGE2[i][j] = GIMAGE1[i-128][j-128];
                CIMAGE2[i][j][0] = CIMAGE1[i-128][j-128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i-128][j-128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i-128][j-128][2];
            }
            if ( options[3] == 2 )
            {
                GIMAGE2[i][j] = GIMAGE1[i-128][j];
                CIMAGE2[i][j][0] = CIMAGE1[i-128][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i-128][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i-128][j][2];
            }
            if ( options[3] == 3 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j-128];
                CIMAGE2[i][j][0] = CIMAGE1[i][j-128][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j-128][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j-128][2];
            }
            if ( options[3] == 4 )
            {
                GIMAGE2[i][j] = GIMAGE1[i][j];
                CIMAGE2[i][j][0] = CIMAGE1[i][j][0];
                CIMAGE2[i][j][1] = CIMAGE1[i][j][1];
                CIMAGE2[i][j][2] = CIMAGE1[i][j][2];
            }

        }

    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE1[i][j] = GIMAGE2[i][j];
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE1[i][j][k] = CIMAGE2[i][j][k];
            }

        }

    }






}

// Function to Skew image
void skew ()
{
    double Degree, x;
    cout << "You picked Skew please enter the degree" << '\n';
    cin >> Degree;
    Degree = ( Degree * 22 ) / ( 180 * 7 );
    x = tan(Degree);
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            GIMAGE2[i][j] = 255;
            for (int k = 0; k < RGB; ++k)
            {
                CIMAGE2[i][j][k] = 255;

            }

        }
    }


    double shrink_value = ( 256 / (1 + (1 / x)));
    double move = SIZE - shrink_value ;
    double step = move / SIZE ;
    shrink_value = shrink_value / SIZE ;
    shrink_value = pow(shrink_value,-1);
    shrink_value = round(shrink_value);
    int shrink_value2 = (int) shrink_value;
    int options;
    cout << "Please specify the type of Skew" << '\n' << "1. Vertical" << '\n' << "2. Horizontal" << '\n';
    cin >> options;
    if ( options == 1 )
    {
        unsigned char skewimage[SIZE][SIZE + (int) move];
        unsigned char skewimagecolored[SIZE][SIZE + (int) move][RGB];

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if ( j * shrink_value2 <= 255)
                {
                    GIMAGE2[i][j] = GIMAGE1[i][j * shrink_value2];
                    CIMAGE2[i][j][0] = CIMAGE1[i][j * shrink_value2][0];
                    CIMAGE2[i][j][1] = CIMAGE1[i][j * shrink_value2][1];
                    CIMAGE2[i][j][2] = CIMAGE1[i][j * shrink_value2][2];
                }


            }
        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];
                CIMAGE1[i][j][0] = CIMAGE2[i][j][0];
                CIMAGE1[i][j][1] = CIMAGE2[i][j][1];
                CIMAGE1[i][j][2] = CIMAGE2[i][j][2];
            }

        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                skewimage[i][j] = 255;
                for (int k = 0; k < RGB; ++k)
                {
                    skewimagecolored[i][j][k] = 255;

                }
            }
        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                skewimage[i][j+(int)move] = GIMAGE1[i][j];
                skewimagecolored[i][j+(int)move][0] = CIMAGE1[i][j][0];
                skewimagecolored[i][j+(int)move][1] = CIMAGE1[i][j][1];
                skewimagecolored[i][j+(int)move][2] = CIMAGE1[i][j][2];

            }
            move -= step;

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = skewimage[i][j];
                CIMAGE1[i][j][0] = skewimagecolored[i][j][0];
                CIMAGE1[i][j][1] = skewimagecolored[i][j][1];
                CIMAGE1[i][j][2] = skewimagecolored[i][j][2];
            }

        }


    }
    if ( options == 2 )
    {
        unsigned char skewimage[SIZE + (int) move][SIZE];
        unsigned char skewimagecolored[SIZE+ (int) move][SIZE][RGB];

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if ( i * shrink_value2 <= 255)
                {
                    GIMAGE2[i][j] = GIMAGE1[i* shrink_value2][j];
                    CIMAGE2[i][j][0] = CIMAGE1[i* shrink_value2][j][0];
                    CIMAGE2[i][j][1] = CIMAGE1[i* shrink_value2][j][1];
                    CIMAGE2[i][j][2] = CIMAGE1[i * shrink_value2][j][2];
                }


            }
        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = GIMAGE2[i][j];
                CIMAGE1[i][j][0] = CIMAGE2[i][j][0];
                CIMAGE1[i][j][1] = CIMAGE2[i][j][1];
                CIMAGE1[i][j][2] = CIMAGE2[i][j][2];
            }

        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                skewimage[i][j] = 255;
                for (int k = 0; k < RGB; ++k)
                {
                    skewimagecolored[i][j][k] = 255;

                }
            }
        }
        for (int j = 0; j < SIZE; ++j)
        {
            for (int i = 0; i < SIZE; ++i)
            {
                skewimage[i+(int)move][j] = GIMAGE1[i][j];
                skewimagecolored[i+(int)move][j][0] = CIMAGE1[i][j][0];
                skewimagecolored[i+(int)move][j][1] = CIMAGE1[i][j][1];
                skewimagecolored[i+(int)move][j][2] = CIMAGE1[i][j][2];

            }
            move -= step;

        }
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                GIMAGE1[i][j] = skewimage[i][j];
                CIMAGE1[i][j][0] = skewimagecolored[i][j][0];
                CIMAGE1[i][j][1] = skewimagecolored[i][j][1];
                CIMAGE1[i][j][2] = skewimagecolored[i][j][2];
            }

        }


    }

}

// Function to Posterize
void Poster ()
{
    int Poster_level = 8;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            CIMAGE1[i][j][0] = round(CIMAGE1[i][j][0] * (Poster_level - 1) / 255) * (255 / (Poster_level - 1));
            CIMAGE1[i][j][1] = round(CIMAGE1[i][j][1] * (Poster_level - 1) / 255) * (255 / (Poster_level - 1));
            CIMAGE1[i][j][2] = round(CIMAGE1[i][j][2] * (Poster_level - 1) / 255) * (255 / (Poster_level - 1));

        }

    }
}


// Function to apply Cyberpunk filter
void Cyberpunk ()
{
    int Poster_level = 8;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int x,y,z;

            x = CIMAGE1[i][j][0] * 2;
            y = CIMAGE1[i][j][1] * 0.5;
            z = CIMAGE1[i][j][2] * 2;
            if ( x > 255 )
            {
                CIMAGE1[i][j][0] = 255;
            }
            else
            {
                CIMAGE1[i][j][0] = x;
            }
            if ( y > 255 )
            {
                CIMAGE1[i][j][1] = 255;
            }
            else
            {
                CIMAGE1[i][j][1] = y;
            }
            if ( z > 255 )
            {
                CIMAGE1[i][j][2] = 255;
            }
            else
            {
                CIMAGE1[i][j][2] = z;
            }

        }

    }
}


// Function for Printing Main Menu
void Main_menu ()
{
    cout << "Welcome to simple image editor" << '\n';
    cout << "1. Make your image Black and White only" << '\n'
         << "2. Make your image Gray scaled like old times (colored images only)" << '\n'
         << "3. Make your image with Inverted colors" << '\n'
         << "4. Merge two images together " << '\n'
         << "5. Flip image" << '\n'
         << "6. Rotate an image" << '\n'
         << "7. Adjust the Brightness of an image" << '\n'
         << "8. Green screen filter (colored images only) " << '\n'
         << "9. Blur Image" << '\n'
         << "10. Enlarge Image" <<'\n'
         << "11. Cyberpunk (colored images only)" <<'\n'
         << "12. Ascii art generator" <<'\n'
         << "13. Oil painting (colored images only)" << '\n'
         << "14. Detect Image Edges" <<'\n'
         << "15. Shrink Image" << '\n'
         << "16. Mirror Image" << '\n'
         << "17. Shuffle Image" << '\n'
         << "18. Crop Image" << '\n'
         << "19. Skew Horizontally / Vertically " << '\n'
         << "20. Increase sharpness" << '\n'
         << "21. Blue filter (colored images only)" << '\n'
         << "22. Sepia filter (colored images only)" << '\n'
         << "23. Mexico filter (colored images only)" << '\n'
         << "24. Oranged filter (colored images only)" << '\n'
         << "25. Exit " << '\n';

}


int main()
{
    while (true)
    {
        int pick;
        Main_menu();
        cin >> pick;
        if ( pick == 25 )
        {
            break;
        }
        loadimage();
        if ( pick == 1 )
        {
            Black_White();
            saveimage();
        }
        else if ( pick == 2 )
        {
            Colored_to_Gray();
            saveimage();
        }
        else if ( pick == 3 )
        {
            Invert_Color();
            saveimage();
        }
        else if ( pick == 4 )
        {
            toMerge();
            saveimage();
        }
        else if ( pick == 5 )
        {
            Flip_Image();
            saveimage();
        }
        else if ( pick == 6 )
        {
            Rotate_Image();
            saveimage();
        }
        else if ( pick == 7 )
        {
            Brightness_adjust();
            saveimage();
        }
        else if ( pick == 8 )
        {
            Greenish_Image();
            saveimage();
        }

        else if ( pick == 9 )
        {
            Blur_Menue();
            saveimage();
        }
        else if ( pick == 10 )
        {
            Enlarge_Image();
            saveimage();
        }
        else if ( pick == 11 )
        {
            Cyberpunk();
            saveimage();
        }
        else if ( pick == 12 )
        {
            Ascii_art();
            cout << "You will find your Ascii art file in cmake-build-debug" << '\n';
        }

        else if ( pick == 13 )
        {
            Poster();
            saveimage();
        }
        else if ( pick == 14 )
        {
            Edge_menu();
            saveimage();
        }
        else if ( pick == 15 )
        {
            Shrink_image();
            saveimage();
        }
        else if ( pick == 16 )
        {
            Mirror_Image();
            saveimage();
        }
        else if ( pick == 17 )
        {
            shuffle();
            saveimage();

        }
        else if ( pick == 18 )
        {
            Crop();
            saveimage();
        }
        else if ( pick == 19 )
        {
            skew();
            saveimage();
        }
        else if ( pick == 20 )
        {
            applySharpnessFilter();
            saveimage();
        }
        else if ( pick == 21 )
        {
            Chanel_swap();
            saveimage();
        }
        else if ( pick == 22 )
        {
            Sepia();
            saveimage();
        }
        else if ( pick == 23 )
        {
            Ektachrome();
            saveimage();
        }
        else if ( pick == 24 )
        {
            Warm_tint_orange();
            saveimage();
        }


    }

    cout << "Thanks for using <(^_^)> " << '\n';

    return 0;
}

