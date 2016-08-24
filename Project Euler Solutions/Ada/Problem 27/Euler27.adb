--Project Euler #27
--n^2 + an + b where |a| < 1000 and |b| < 1000
--Find the product of the coefficients, a and b, for the quadratic expression
--that produces the maximum number of primes for consecutive
--values of n, starting with n = 0. 

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler27 is

  package IO renames Ada.Text_IO;

  type IntArray is array (Positive range <>) of Integer;

  function isNewPrime(P : IntArray; N : Integer) return Boolean is
    I : Integer := 1;    
  begin
    while P(I) <= N loop
      if P(I) = N then
        return True;
      end if;
      I := I + 1;
      if I = P'Length then
        goto endOfFunction;
      end if;
    end loop;
    <<endOfFunction>>
    return False;
  end isNewPrime;
  
  function isPrime(N : Long_Long_Integer) return Boolean is
    J : Integer := 2;
  begin
    if N = 2 then
      return True;
    end if;
    if N < 2 then
      return False;
    end if;
    <<Prime_Loop>>
    if N mod Long_Long_Integer(J) = 0 then
      return False;
    end if;
    J := J + 1;
    if Long_Long_Integer(J) < N then
      goto Prime_Loop;
    end if;
    return True;
  end isPrime;

  --Variable Declarations
  Answer, Aanswer, Banswer, Nanswer : Integer := 0;
  Count, PrevCount : Integer := 1;
  Partial : Long_Long_Integer := 0;
  PrimeArray : IntArray (Positive range 1..1000) := (others => 0);
  
begin

  for I in 1..1000 loop
    if isPrime(Long_Long_Integer(I)) then
      PrimeArray(Count) := I;
      Count := Count + 1;
    end if;
  end loop;

  Count := 0;
  First_Loop:
  for A in -999..999 loop
    if A mod 2 /= 0 then
      Second_Loop:
      for B in -999..999 loop
        declare
          N : Integer := 0;
        begin
          if isNewPrime(PrimeArray, B) = True and then (1 + A + B) mod 2 /= 0 then
            while isNewPrime(PrimeArray, Abs(N * N + A * N + B)) loop
              N := N + 1;
            end loop;
          end if;
          if N > Nanswer then
            Nanswer := N;
            Banswer := B;
            Aanswer := A;
            Answer := A*B;
          end if;
        end;
      end loop Second_Loop;
    end if;
  end loop First_Loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler27;