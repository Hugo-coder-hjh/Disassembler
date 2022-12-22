.CODE
.ADDR x1000

    ADD R0, R1, R2
    MUL R2, R3, R1
    DIV R1, R1, R4
    ADD R1, R0, #15

EMPTY_LABEL            ;; test the EMPTY_LABEL

.DATA                  ;; test different location
.ADDR x4000
.FILL x1001