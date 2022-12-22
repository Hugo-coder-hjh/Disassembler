BEFORE             ;; test the label before code
.CODE
.ADDR x0010
LABEL1
ADD R3, R3, #-5

.CODE			   ;; There is more than one CODE section
.ADDR x0005
LABEL2
ADD R1, R1, #-16   ;; test the range of the IMM
ADD R2, R2, #15    ;; test the range of the IMM