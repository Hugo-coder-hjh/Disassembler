  .DATA                
  .ADDR x6000          

global_string            ;; test the label for data memory  
  .FILL x34            
  .FILL x25            
  .FILL x5A           
  .FILL x85           
  .FILL x7C           
  .FILL x26            
  .FILL x32           
  .FILL x4D           
  .FILL x2F           
  .FILL #5             

.CODE
.ADDR x0000
CODE1
ADD R1, R1, #-16   
ADD R2, R2, #15

  .DATA                
  .ADDR x7000          

STRING2                 ;; test multiple DATA regions
  .FILL x34            
  .FILL x25            
  .FILL x5A           
  .FILL x85           
           
.CODE                   ;; test multiple CODE regions
.ADDR x0020
CODE2
ADD R1, R1, #1          ;; test 5 different ISAs
ADD R2, R2, R5
MUL R0, R1, R2
SUB R3, R2, R1
DIV R1, R3, R2

END