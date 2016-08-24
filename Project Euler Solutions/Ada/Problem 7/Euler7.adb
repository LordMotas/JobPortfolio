--Project Euler #7
--By listing the first six prime numbers: 2,3,5,7,11, and 13,
--we can see that the 6th prime is 13.
--What is the 10001st prime number?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Euler7 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  I : Integer := 2;
  count : Integer := 0;
  J : Integer;
  answer : Integer;

  function isPrime (number : Integer) return Boolean is
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
    --Check if prime
    if isPrime(I) then
      count := count + 1;
    end if;
  answer := I;
  if I = 2 then
    I := I + 1;
  else
    I := I + 2;
  end if;
  if count /= 10001 then
    goto First_Loop;
  end if;
IO.New_Line;
IO.Put_Line("The answer is: " & Integer'Image(answer));

end Euler7;