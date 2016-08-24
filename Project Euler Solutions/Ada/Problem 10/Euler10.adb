--Project Euler #10
--The sume of primes below 10 is 2+3+5+7=17
--Find the sum of all the primes below two million

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler10 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  answer : Long_Integer := 0;
  J : Long_Integer;
  I : Long_Integer := 1;

  function isPrime(number : Long_Integer) return Boolean is
  begin
    J := 2;
    if number = 2 then
      return True;
    end if;
    if number < 2 then
      return False;
    end if;
    <<Prime_Loop>>
    if number mod J = 0 then
      return False;
    end if;
    J := J + 1;
    if J < number then
      goto Prime_Loop;
    end if;
    return True;
  end isPrime;
  
begin
  <<First_Loop>>
  if isPrime(I) then
    answer := answer + I;
  end if;
  I := I + 2;
  if I < 2000000 then
    goto First_Loop;
  end if;

  IO.Put_Line("The answer is: "&Long_Integer'Image(answer + 2));
  
end Euler10;