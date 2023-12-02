# **Image editor Algorithms used in pseudocode**

### notes :

- A Gray Scaled Image is a 2D array of [width][height] each pixel has a value corresponding to its gray value.

- A Colored Image is a 3D array of [width][height][RGB] each pixel has three values corresponding to its Red scale, Green scale, and Blue scale.

- GIMAGE1 stands for (gray image 1), GIMAGE2 stands for (gray image 2), and at the end we print one of them based on where the edited version was saved. 

- CIMAGE1 stands for (colored image 1), CIMAGE2 stands for (colored image 2), and at the end we print one of them based on where the edited version was saved. 

**Black and White Image :**
```
average = 0

FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        average = average + GIMAGE1[i][j]
    END FOR
END FOR

tmp = average / 65536

FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        IF GIMAGE1[i][j] >= tmp THEN
            GIMAGE1[i][j] = 255
        ELSE
            GIMAGE1[i][j] = 0
        END IF
    END FOR
END FOR
```




**Invert Image :**

```
FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        GIMAGE1[i][j] = 255 - GIMAGE1[i][j]
    END FOR
END FOR
```

**Merge :**
```
FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        GIMAGE1[i][j] = (GIMAGE1[i][j] + GIMAGE2[i][j]) / 2
    END FOR
END FOR
```

**Rotate Image**

rotate 90 degree
```
FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM SIZE - 1 DOWNTO 0 DO
        GIMAGE2[i][(SIZE - 1) - j] = GIMAGE1[j][i]
    END FOR
END FOR

```

The whole rotating function :
```

OUTPUT "1. Rotate by 90 degrees"
OUTPUT "2. Rotate by 180 degrees"
OUTPUT "3. Rotate by 270 degrees"
INPUT options

IF options EQUALS 1 THEN
    CALL rotate_90_degree()
END IF

IF options EQUALS 2 THEN
    CALL rotate_90_degree()
    CALL rotate_90_degree()
END IF

IF options EQUALS 3 THEN
    CALL rotate_90_degree()
    CALL rotate_90_degree()
    CALL rotate_90_degree()
END IF
```



**Flip Image :**
We flip the image horizontally then if we wanted it to be flipped vertically we just rotate 180 degree
 ```
 
OUTPUT "You picked flip image"
OUTPUT "1. Flip horizontally"
OUTPUT "2. Flip vertically"
INPUT fliper


    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM SIZE - 1 DOWNTO 0 DO
            GIMAGE2[i][j] = GIMAGE1[i][(SIZE - 1) - j]
        END FOR
    END FOR

    IF fliper EQUALS 2 THEN
        CALL rotate_90_degree()
        CALL rotate_90_degree()
    END IF

 ```

**Darken and Lighten Image :**

Increase brightness :

```
FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        INT tmp 
        tmp = (GIMAGE1[i][j] * 0.5) + GIMAGE1[i][j]
        IF tmp >= 255 THEN
            GIMAGE1[i][j] = 255
        ELSE
            GIMAGE1[i][j] = (GIMAGE1[i][j] * 0.5) + GIMAGE1[i][j]
        END IF
    END FOR
END FOR
```

Decrease brightness :

```
FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        INT tmp 
        tmp = GIMAGE1[i][j] - (GIMAGE1[i][j] * 0.5)
        IF tmp <= 0 THEN
            GIMAGE1[i][j] = 0
        ELSE
            GIMAGE1[i][j] = GIMAGE1[i][j] - (GIMAGE1[i][j] * 0.5)
        END IF
    END FOR
END FOR
```


**Detect Image Edges :**
```
FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        INT detector = 30
        INT pencil = 95

        IF i > 0 AND j > 0 AND i < SIZE - 1 AND j < SIZE - 1 THEN
            IF ABS(GIMAGE1[i][j] - GIMAGE1[i + 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i - 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j + 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j - 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF
        ELSE IF i == 0 AND j < SIZE - 1 AND j > 0 THEN
            IF ABS(GIMAGE1[i][j] - GIMAGE1[i + 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j + 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j - 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF
        ELSE IF i == 0 AND j == SIZE - 1 THEN
            IF ABS(GIMAGE1[i][j] - GIMAGE1[i + 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j - 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF
        ELSE IF i == SIZE - 1 AND j < SIZE - 1 AND j > 0 THEN
            IF ABS(GIMAGE1[i][j] - GIMAGE1[i - 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j + 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j - 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF
        ELSE IF i == SIZE - 1 AND j == SIZE - 1 THEN
            IF ABS(GIMAGE1[i][j] - GIMAGE1[i - 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j - 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF
        ELSE IF i == 0 AND j == 0 THEN
            IF ABS(GIMAGE1[i][j] - GIMAGE1[i + 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j + 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF
        ELSE IF i == SIZE - 1 AND j == 0 THEN
            IF ABS(GIMAGE1[i][j] - GIMAGE1[i - 1][j]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF

            IF ABS(GIMAGE1[i][j] - GIMAGE1[i][j + 1]) > detector THEN
                GIMAGE2[i][j] = pencil
                CONTINUE
            END IF
        END IF

        GIMAGE2[i][j] = 255
    END FOR
END FOR
```



**Enlarge Image :**

```

OUTPUT "Please pick enlarged quarter"
OUTPUT "1 | 2"
OUTPUT "3 | 4"
INPUT options


    IF options EQUALS 1 THEN
        FOR i FROM 0 TO SIZE - 1 DO
            FOR j FROM 0 TO SIZE - 1 DO
                GIMAGE2[i][j] = GIMAGE1[i/2][j/2]
            END FOR
        END FOR
    END IF

    IF options EQUALS 2 THEN
        FOR i FROM 0 TO SIZE - 1 DO
            FOR j FROM 0 TO SIZE - 1 DO
                GIMAGE2[i][j] = GIMAGE1[i/2][j/2 + 127]
            END FOR
        END FOR
    END IF

    IF options EQUALS 3 THEN
        FOR i FROM 0 TO SIZE - 1 DO
            FOR j FROM 0 TO SIZE - 1 DO
                GIMAGE2[i][j] = GIMAGE1[i/2 + 127][j/2]
            END FOR
        END FOR
    END IF

    IF options EQUALS 4 THEN
        FOR i FROM 0 TO SIZE - 1 DO
            FOR j FROM 0 TO SIZE - 1 DO
                GIMAGE2[i][j] = GIMAGE1[i/2 + 127][j/2 + 127]
            END FOR
        END FOR
    END IF

```
**Shrink Image :**
```

OUTPUT "1. Shrink to 1/2"
OUTPUT "2. Shrink to 1/3"
OUTPUT "3. Shrink to 1/4"
INPUT options


    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            IF options EQUALS 1 AND i * 2 <= 255 AND j * 2 <= 255 THEN
                GIMAGE2[i][j] = GIMAGE1[i * 2][j * 2]
            ELSE IF options EQUALS 2 AND i * 3 <= 255 AND j * 3 <= 255 THEN
                GIMAGE2[i][j] = GIMAGE1[i * 3][j * 3]
            ELSE IF options EQUALS 3 AND i * 4 <= 255 AND j * 4 <= 255 THEN
                GIMAGE2[i][j] = GIMAGE1[i * 4][j * 4]
            END IF
        END FOR
    END FOR

```
**Mirror Image:**
```

OUTPUT "1. Right Mirror"
OUTPUT "2. Left Mirror"
OUTPUT "3. Top Mirror"
OUTPUT "4. Down Mirror"
INPUT options


    IF options EQUALS 1 THEN
        FOR i FROM 0 TO SIZE - 1 DO
            FOR j FROM 0 TO 127 DO
                GIMAGE1[i][j] = GIMAGE1[i][SIZE - 1 - j]
            END FOR
        END FOR
    END IF

    IF options EQUALS 2 THEN
      FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM SIZE - 1 DOWNTO 0 DO
        GIMAGE2[i][j] = GIMAGE1[i][SIZE - 1 - j]
       END FOR
      END FOR
        FOR i FROM 0 TO SIZE - 1 DO
            FOR j FROM 127 TO SIZE - 1 DO
                GIMAGE1[i][j] = GIMAGE2[i][j]
            END FOR
        END FOR
    END IF

    IF options EQUALS 3 THEN
        FOR i FROM 0 TO 127 DO
            FOR j FROM 0 TO SIZE - 1 DO
                GIMAGE1[SIZE - 1 - i][j] = GIMAGE1[i][j]
            END FOR
        END FOR
    END IF

    IF options EQUALS 4 THEN
        FOR i FROM 0 TO 127 DO
            FOR j FROM 0 TO SIZE - 1 DO
                GIMAGE1[i][j] = GIMAGE1[SIZE - 1 - i][j]
            END FOR
        END FOR
    END IF

```


**Shuffle Image :**
```
DECLARE options[4]
OUTPUT "1 | 2"
OUTPUT "3 | 4"
FOR i FROM 0 TO 3 DO
    INPUT options[i]
    IF options[i] > 4 OR options[i] < 1 THEN
        OUTPUT "This quad doesn't exist. Please try again."
        RETURN
    END IF
END FOR
// Quad 1 deciding
FOR i FROM 0 TO 127 DO
    FOR j FROM 0 TO 127 DO
        IF options[0] EQUALS 1 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j]
        ELSE IF options[0] EQUALS 2 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j + 128]

        ELSE IF options[0] EQUALS 3 THEN
            GIMAGE2[i][j] = GIMAGE1[i + 128][j]

        ELSE IF options[0] EQUALS 4 THEN
            GIMAGE2[i][j] = GIMAGE1[i + 128][j + 128]
 
        END IF
    END FOR
END FOR

// Quad 2 deciding
FOR i FROM 0 TO 127 DO
    FOR j FROM 128 TO SIZE - 1 DO
        IF options[1] EQUALS 1 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j - 128]

        ELSE IF options[1] EQUALS 2 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j]

        ELSE IF options[1] EQUALS 3 THEN
            GIMAGE2[i][j] = GIMAGE1[i + 128][j - 128]

        ELSE IF options[1] EQUALS 4 THEN
            GIMAGE2[i][j] = GIMAGE1[i + 128][j]

        END IF
    END FOR
END FOR

// Quad 3 deciding
FOR i FROM 128 TO SIZE - 1 DO
    FOR j FROM 0 TO 127 DO
        IF options[2] EQUALS 1 THEN
            GIMAGE2[i][j] = GIMAGE1[i - 128][j]
 
        ELSE IF options[2] EQUALS 2 THEN
            GIMAGE2[i][j] = GIMAGE1[i - 128][j + 128]
 
        ELSE IF options[2] EQUALS 3 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j]

        ELSE IF options[2] EQUALS 4 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j + 128]

        END IF
    END FOR
END FOR

// Quad 4 deciding
FOR i FROM 128 TO SIZE - 1 DO
    FOR j FROM 128 TO SIZE - 1 DO
        IF options[3] EQUALS 1 THEN
            GIMAGE2[i][j] = GIMAGE1[i - 128][j - 128]

        ELSE IF options[3] EQUALS 2 THEN
            GIMAGE2[i][j] = GIMAGE1[i - 128][j]

        ELSE IF options[3] EQUALS 3 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j - 128]

        ELSE IF options[3] EQUALS 4 THEN
            GIMAGE2[i][j] = GIMAGE1[i][j]

        END IF
    END FOR
END FOR
```
 

**Blur Image :**
```
FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        INT average = 0

        IF i > 0 AND j > 0 AND i < SIZE-1 AND j < SIZE-1 THEN
            average += GIMAGE1[i-1][j] // pixel above center
            average += GIMAGE1[i+1][j] // pixel below center
            average += GIMAGE1[i][j+1] // pixel on the right of center
            average += GIMAGE1[i][j-1] // pixel on the left of center
            average += GIMAGE1[i-1][j-1] // upper-left corner
            average += GIMAGE1[i-1][j+1] // upper-right corner
            average += GIMAGE1[i+1][j-1] // lower-left corner
            average += GIMAGE1[i+1][j+1] // lower-right corner
            average += GIMAGE1[i][j] // the center
            average = average / 9
        ELSE IF i == 0 AND j < SIZE-1 THEN
            average += GIMAGE1[i+1][j]
            average += GIMAGE1[i+1][j+1]
            average += GIMAGE1[i][j+1]
            average += GIMAGE1[i][j]
            average = average / 4
        ELSE IF i == 0 AND j == SIZE-1 THEN
            average += GIMAGE1[i+1][j]
            average += GIMAGE1[i+1][j-1]
            average += GIMAGE1[i][j-1]
            average += GIMAGE1[i][j]
            average = average / 4
        ELSE IF i == SIZE-1 AND j < SIZE-1 THEN
            average += GIMAGE1[i-1][j]
            average += GIMAGE1[i-1][j+1]
            average += GIMAGE1[i][j+1]
            average += GIMAGE1[i][j]
            average = average / 4
        ELSE IF i == SIZE-1 AND j == SIZE-1 THEN
            average += GIMAGE1[i-1][j]
            average += GIMAGE1[i-1][j-1]
            average += GIMAGE1[i][j-1]
            average += GIMAGE1[i][j]
            average = average / 4
        ELSE
            average += GIMAGE1[i-1][j]
            average += GIMAGE1[i-1][j-1]
            average += GIMAGE1[i+1][j]
            average += GIMAGE1[i][j]
            average = average / 4
        END IF

        GIMAGE2[i][j] = average
    END FOR
END FOR
```

**Crop Image :**

```

INPUT x
INPUT y
INPUT l
INPUT w
    FOR i FROM x TO x + l - 1 DO
        FOR j FROM y TO y + w - 1 DO
            GIMAGE2[i][j] = GIMAGE1[i][j]
        END FOR
    END FOR
```


**Skew Horizontally / Vertically  :**
```
DECLARE Degree, x
OUTPUT "You picked Skew, please enter the degree:"
INPUT Degree
Degree = (Degree * 22) / (180 * 7)
x = tan(Degree)

FOR i FROM 0 TO SIZE - 1 DO
    FOR j FROM 0 TO SIZE - 1 DO
        GIMAGE2[i][j] = 255
    END FOR
END FOR

DECLARE shrink_value
DECLARE move
DECLARE step
shrink_value = 256 / (1 + (1 / x))
move = SIZE - shrink_value
step = move / SIZE
shrink_value = shrink_value / SIZE
shrink_value = pow(shrink_value, -1)
shrink_value = round(shrink_value)
DECLARE shrink_value2
shrink_value2 = CAST(shrink_value TO INTEGER)

DECLARE options
OUTPUT "Please specify the type of Skew:"
OUTPUT "1. Vertical"
OUTPUT "2. Horizontal"
INPUT options

IF options EQUALS 1 THEN
    DECLARE skewimage[SIZE][SIZE + (int) move]
    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            IF j * shrink_value2 <= 255 THEN
                GIMAGE2[i][j] = GIMAGE1[i][j * shrink_value2]

            END IF
        END FOR
    END FOR

    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            GIMAGE1[i][j] = GIMAGE2[i][j]

        END FOR
    END FOR

    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            skewimage[i][j + (int) move] = GIMAGE1[i][j]

        END FOR
            move = move - step
    END FOR

    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            GIMAGE1[i][j] = skewimage[i][j]

        END FOR
    END FOR
END IF
IF options EQUALS 2 THEN
    DECLARE skewimage[SIZE + (int) move][SIZE]

    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            IF i * shrink_value2 <= 255 THEN
                GIMAGE2[i][j] = GIMAGE1[i * shrink_value2][j]

            END IF
        END FOR
    END FOR

    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            GIMAGE1[i][j] = GIMAGE2[i][j]

        END FOR
    END FOR

    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            skewimage[i][j] = 255
        END FOR
    END FOR

    FOR j FROM 0 TO SIZE - 1 DO
        FOR i FROM 0 TO SIZE - 1 DO
            skewimage[i + (int) move][j] = GIMAGE1[i][j]
          
        END FOR
						move = move - step
    END FOR

    FOR i FROM 0 TO SIZE - 1 DO
        FOR j FROM 0 TO SIZE - 1 DO
            GIMAGE1[i][j] = skewimage[i][j]
        END FOR
    END FOR
END IF
```



**Gray scaled Image (for colored only) :**

```
for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        average = 0
        for k = 0 to RGB - 1
            average = average + CIMAGE1[i][j][k]
        end for
        tmp = average / 3
        CIMAGE1[i][j][0] = tmp
        CIMAGE1[i][j][1] = tmp
        CIMAGE1[i][j][2] = tmp
    end for
end for
```


1. Inside the innermost loop, the code calculates the  **average** value for the current pixel (i, j). It does this by summing up the color values for all three channels (R, G, B) of the pixel.
1. After the innermost loop completes, the code calculates the  **tmp** value by dividing the  **average** by 3. This step effectively computes the average color value for the pixel.
1. Finally, the code sets all three color channels (R, G, B) of the pixel to the  **tmp** value, effectively converting the pixel to grayscale.



**Green screen filter (colored images only) :**

```
for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        CIMAGE1[i][j][0] = 0.299 * CIMAGE1[i][j][0]
        CIMAGE1[i][j][1] = 0.587 * CIMAGE1[i][j][1]
        CIMAGE1[i][j][2] = 0.114 * CIMAGE1[i][j][2]
    end for
end for
```

1. The outermost loop ( **for i = 0 to SIZE - 1** ) iterates over the rows of the image.
1. Inside the outer loop, there's another loop ( **for j = 0 to SIZE - 1** ) that iterates over the columns of the image.
1. For each pixel at position (i, j) in the image, the code applies a specific weight to each color channel (R, G, B). The weights used are 0.299 for the red channel (CIMAGE1[i][j][0]), 0.587 for the green channel (CIMAGE1[i][j][1]), and 0.114 for the blue channel (CIMAGE1[i][j][2]).
1. The result of these weighted calculations is stored back in the corresponding color channels (R, G, B) of the pixel. This process effectively converts the image to grayscale, using the luminance values of each channel.

**Cyberpunk (colored images only) :**

```
for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        x = CIMAGE1[i][j][0] * 2
        y = CIMAGE1[i][j][1] * 0.5
        z = CIMAGE1[i][j][2] * 2

        if x > 255
            CIMAGE1[i][j][0] = 255
        else
            CIMAGE1[i][j][0] = x

        if y > 255
            CIMAGE1[i][j][1] = 255
        else
            CIMAGE1[i][j][1] = y

        if z > 255
            CIMAGE1[i][j][2] = 255
        else
            CIMAGE1[i][j][2] = z
    end for
end for
```


1. The code enters two nested loops to iterate over the rows and columns of the image, denoted by  **i** and  **j** .
1. For each pixel at position (i, j) in the image, the code applies color adjustments to each color channel (R, G, B) separately.
1. The adjustments are as follows:
- The red channel (CIMAGE1[i][j][0]) is doubled by multiplying it by 2, effectively enhancing red tones.
  - The green channel (CIMAGE1[i][j][1]) is halved by multiplying it by 0.5, reducing its intensity.
- The blue channel (CIMAGE1[i][j][2]) is doubled by multiplying it by 2, enhancing blue tones.
4. After these adjustments, there are conditional checks for each color channel to ensure that they do not exceed the valid color range (0-255). If a value is greater than 255, it is clamped to 255.
4. The modified color channels are stored back in the  **CIMAGE1** array, effectively intensifying certain colors and achieving the cyberpunk filter effect.

**Ascii art generator :** 

1) We need to convert colored images to gray-scaled ones using the previous algorithm.
1) We need to know how to output to a .txt file.
3) Shrink the image to one-fifth using the following algorithm :

```
for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        if i * 5 <= 255 and j * 5 <= 255
            GIMAGE2[i][j] = GIMAGE1[i * 5][j * 5]
        end if
    end for
end for
```

4) Apply the following process :

```
Create a new file named "ASCIIART.txt"
Open the file for writing (output stream)

for i = 0 to 53
    for j = 0 to 53
        if GIMAGE1[i][j] < 120
            Write a period (.) to the file
        else
            Write a space to the file
        end if
    end for
    Write a newline character ('\n') to the file
end for

Close the file
```


1. It begins by creating a new file named "ASCIIART.txt" to store the ASCII art.
1. The file is opened for writing, allowing data to be written to it.
1. Two nested loops iterate through the  **GIMAGE1** array, which has dimensions of 54x54. These loops correspond to the rows (i) and columns (j) of the ASCII art.
1. For each pixel at position (i, j) in  **GIMAGE1** , it checks if the pixel's intensity (the value in  **GIMAGE1[i][j]** ) is less than 120. If it is, the code writes a period ('.') to the file, which represents a darker pixel in the ASCII art. Otherwise, it writes a space (' '), which represents a lighter pixel.

**Oil painting (colored images only) :** 

```
Poster_level = 8
for i = 0 to SIZE - 1
 for j = 0 to SIZE - 1
  CIMAGE1[i][j][0] = round(CIMAGE1[i][j][0]*(Poster_level-1)/255)*(255/(Poster_level- 1))
  CIMAGE1[i][j][1] = round(CIMAGE1[i][j][1]*(Poster_level-1)/255)*(255/(Poster_level- 1))
  CIMAGE1[i][j][2] = round(CIMAGE1[i][j][2]*(Poster_level-1)/255)*(255/(Poster_level- 1))
  end for
end for
```

1. The  **Poster\_level** is set to 8, indicating the number of posterization levels. A higher value leads to a more pronounced posterization effect.
1. The code enters two nested loops to iterate over the rows and columns of the image, denoted by  **i** and  **j** .
1. For each pixel at position (i, j) in the image, the code applies posterization to each color channel (R, G, B) separately.
1. The formula used to perform posterization involves the following steps:
- The color channel is first multiplied by  **(Poster\_level - 1) / 255** .
  - The result is rounded to the nearest integer value using the  **round** function.
    - The rounded value is then multiplied by  **255 / (Poster\_level - 1)** .
5. These calculations effectively quantize the color channels to a smaller number of discrete values, producing the posterization effect.
5. The modified color channels are stored back in the  **CIMAGE1** array, preserving the original color channels.

**Increase sharpness :**
```
int kerne[3][3] ={
        {-1, -1, -1},
        {-1,  9, -1},
        {-1, -1, -1}}
```
```
for c = 0 to RGB - 1
    for x = 1 to SIZE - 2
        for y = 1 to SIZE - 2
            sum = 0
            for i = -1 to 1
                for j = -1 to 1
                    sum = sum + CIMAGE1[x + i][y + j][c] * kernel[i + 1][j + 1]
                end for
            end for
            CIMAGE2[x][y][c] = max(0, min(255, sum))
        end for
    end for

```

1. The outermost loop ( **for c = 0 to RGB - 1** ) iterates over the three color channels (Red, Green, Blue).
1. The next two loops ( **for x** and  **for y** ) iterate over the pixels of the image, excluding the border pixels ( **1** to  **SIZE - 2** ). These loops represent the spatial dimensions of the image.
1. Within the inner loops, there is a nested loop that goes from  **i = -1** to  **1** and  **j = -1![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.034.png)** to  **1** . This loop performs a convolution operation with a 3x3 kernel ( **kernel** ) centered at the current pixel ![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.035.png) **(x, y)** for the current color channel  **c** . The convolution calculates a weighted sum of neighboring pixel values, where the weights are defined by the  **kernel2** matrix.
1. The result of the convolution, represented by the  **sum**, is clamped to the 0-255 range to ensure it doesn't exceed the valid color range.![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.036.png)
1. The clamped result is stored in the corresponding location in the  **CIMAGE2** array, enhancing the sharpness of the image.

**Blue filter (colored images only) :**

```
for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        CIMAGE2[i][j][0] = CIMAGE1[i][j][2]
        CIMAGE2[i][j][1] = CIMAGE1[i][j][1]
        CIMAGE2[i][j][2] = CIMAGE1[i][j][0]
    end for
end for
```

1. The outermost loop ( **for i = 0 to SIZE - 1** ) iterates over the rows of the image.
1. Inside the outer loop, there's another loop ( **for j = 0 to SIZE - 1** ) that iterates over the columns of the image.
1. For each pixel at position (i, j) in the image, the code swaps the color channels by copying the red channel (CIMAGE1[i][j][2]) to the blue channel (CIMAGE2[i][j][0]), the green channel (CIMAGE1[i][j][1]) to the green channel (CIMAGE2[i][j][1]), and the blue channel (CIMAGE1[i][j][0]) to the red channel (CIMAGE2[i][j][2]).
1. The result is stored in the  **CIMAGE2** array, effectively reversing the red and blue color channels for each pixel.

**Sepia filter (colored images only) :**

```
for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        x = 0.393 * CIMAGE1[i][j][0] + 0.769 * CIMAGE1[i][j][1] + 0.189 * CIMAGE1[i][j][2]
        y = 0.349 * CIMAGE1[i][j][0] + 0.686 * CIMAGE1[i][j][1] + 0.168 * CIMAGE1[i][j][2]
        z = 0.272 * CIMAGE1[i][j][0] + 0.534 * CIMAGE1[i][j][1] + 0.131 * CIMAGE1[i][j][2]

        if x > 255
            CIMAGE2[i][j][0] = 255
        else
            CIMAGE2[i][j][0] = x

        if y > 255
            CIMAGE2[i][j][1] = 255
        else
            CIMAGE2[i][j][1] = y

        if z > 255
            CIMAGE2[i][j][2] = 255
        else
            CIMAGE2[i][j][2] = z
    end for
end for
```

1. The outermost loop ( **for i = 0 to SIZE - 1** ) iterates over the rows of the image.
1. Inside the outer loop, there's another loop ( **for j = 0 to SIZE - 1** ) that iterates over the columns of the image.
1. For each pixel at position (i, j) in the image, the code calculates three new values, **x** ,  **y** , and  **z** , based on weighted combinations of the original RGB color channels.![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.040.png)
1. The values  **x** ,  **y** , and  **z** represent the transformed color channels for the sepia effect. The specific weights applied in the calculations create the sepia tone.
1. For each of the transformed values ( **x** ,  **y** , and  **z** ), there is a check to ensure that the value does not exceed 255. If any of them do, they are clamped to 255 to prevent values outside the valid color range.
1. The transformed color channels are then stored in the  **CIMAGE2** array, effectively creating a sepia-toned version of the original image.

**Mexico filter (colored images only) :**

```
tint_value = 30

for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        x = CIMAGE1[i][j][0] + tint_value
        y = CIMAGE1[i][j][1] + tint_value
        z = CIMAGE1[i][j][2] - tint_value

        if x > 255
            CIMAGE2[i][j][0] = 255
        else
            CIMAGE2[i][j][0] = x

        if y > 255
            CIMAGE2[i][j][1] = 255
        else
            CIMAGE2[i][j][1] = y

        if z > 255
            CIMAGE2[i][j][2] = 255
        else if z < 0
            CIMAGE2[i][j][2] = 0
        else
            CIMAGE2[i][j][2] = z
    end for
end for
```

1. The  **tint\_value** is set to 30, indicating the strength of the tint to be applied. This value determines how much each color channel will be modified for the Mexico filter.
1. The code enters two nested loops to iterate over the rows and columns of the image, denoted by  **i** and  **j** .
1. For each pixel at position (i, j) in the image, the code calculates three new values, 

   **x** ,  **y** , and  **z** . Each value is obtained by adding or subtracting the  **tint\_value** to the corresponding color channel (R, G, B).![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.043.png)![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.044.png)

4. There are conditional checks for  **x** ,  **y** , and  **z** to ensure that they do not exceed the valid color range (0-255). If a value is greater than 255, it is clamped to 255. If a value is less than 0, it is clamped to 0. Otherwise, the original values are used.
4. The modified color channels ( **x** ,  **y** , and  **z** ) are stored in the corresponding location in the ![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.045.png) **CIMAGE2** array.

**Oranged filter (colored images only) :**

```
tint_value = 50

for i = 0 to SIZE - 1
    for j = 0 to SIZE - 1
        x = CIMAGE1[i][j][0] + tint_value
        y = CIMAGE1[i][j][0] - tint_value

        if x > 255
            CIMAGE2[i][j][0] = 255
        else
            CIMAGE2[i][j][0] = x

        if y > 255
            CIMAGE2[i][j][1] = 255
        else if y < 0
            CIMAGE2[i][j][1] = 0
        else
            CIMAGE2[i][j][1] = y

        CIMAGE2[i][j][2] = CIMAGE1[i][j][2]
    end for
end for
```

1. The  **tint\_value** is set to 50, indicating the strength of the tint to be applied. This value determines how much the red channel will be modified for the orange filter.
1. The code then enters two nested loops to iterate over the rows and columns of the image, denoted by  **i** and  **j** .
1. For each pixel at position (i, j) in the image, the code calculates two new values,  **x ![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.047.png)**and  **y** . The value  **x** is obtained by adding the  **tint\_value** to the red channel (CIMAGE1[i][j][0]), while the value  **y** is obtained by subtracting the  **tint\_value** .
1. There are conditional checks for  **x** and  **y** to ensure that they do not exceed the![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.048.png)

   valid color range (0-255). If  **x** is greater than 255, it is clamped to 255. If  **y** is less than 0, it is clamped to 0. Otherwise, the original values are used.

5. The modified red channel ( **x** or  **y** ) is stored in the corresponding location in the **CIMAGE2** array, preserving the green and blue channels.![](Aspose.Words.06836027-63ed-44b7-bb22-6feae950ef5b.049.png)



