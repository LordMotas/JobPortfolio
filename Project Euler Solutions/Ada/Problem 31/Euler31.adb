--Project Euler #31
--How many different ways can 200p be made using any number of coins?
--1p,2p,5p,10p,20p,50p,100p,200p can be used

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler31 is

  package IO renames Ada.Text_IO;

  --Variable Declarations
  Answer : Integer := 0;
  I, J, K, L, M, N, O : Integer := 0;
  Target : Integer := 200;

begin

  I := Target;
  <<First_Loop>>
    J := I;
    <<Second_Loop>>
      K := J;
      <<Third_Loop>>
        L := K;
        <<Fourth_Loop>>
          M := L;
          <<Fifth_Loop>>
            N := M;
            <<Sixth_Loop>>
              O := N;
              <<Seventh_Loop>>
                Answer := Answer + 1;
              O := O - 2;
              if O >= 0 then
                goto Seventh_Loop;
              end if;
            N := N - 5;
            if N >= 0 then
              goto Sixth_Loop;
            end if;
          M := M - 10;
          if M >= 0 then
            goto Fifth_Loop;
          end if;
        L := L - 20;
        if L >= 0 then
          goto Fourth_Loop;
        end if;
      K := K - 50;
      if K >= 0 then
        goto Third_Loop;
      end if;
    J := J - 100;
    if J >= 0 then
      goto Second_Loop;
    end if;
  I := I - 200;
  if I >= 0 then
    goto First_Loop;
  end if;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler31;