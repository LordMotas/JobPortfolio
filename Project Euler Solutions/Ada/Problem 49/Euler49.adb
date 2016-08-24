--Project Euler #49
--Each of the terms are prime and each of the 4-digit numbers are permutations
--What 12-digit number do you form by concatenating the three terms in this sequence

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler49 is

  package IO renames Ada.Text_IO;
  package IIO renames Ada.Integer_Text_IO; 
  package SU renames Ada.Strings.Unbounded;

  function isPrime(number : Integer) return Boolean is
    J : Integer;
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

  function isPerm(M : Integer; N : Integer) return Boolean is
    Temp : Integer := N;
    Arr : array(0..9) of Integer := (0..9 => 0);
  begin
    while Temp > 0 loop
      Arr(Temp mod 10) := Arr(Temp mod 10) + 1;
      Temp := Temp / 10;
    end loop;
    Temp := M;
    while Temp > 0 loop
      Arr(Temp mod 10) := Arr(Temp mod 10) - 1;
      Temp := Temp / 10;
    end loop;
    for I in 0..9 loop
      if Arr(I) /= 0 then
        return False;
      end if;
    end loop;
    return True;
  end isPerm;

  --Variable Declarations
  Answer : String(1..12);
  Count : Integer := 0;
  Primes : array(0..10000) of Integer;
  InArray : Boolean := False;

begin

  for I in 1489..10000 loop
    if isPrime(I) then
      Primes(Count) := I;
      Count := Count + 1;
    end if;
  end loop;

  for I in 0..Count loop
    for J in I+1..Count loop
      declare
        K : Integer := Primes(J) + (Primes(J) - Primes(I));
      begin
        for L in 1..Count loop
          if Primes(L) = K then
            InArray := true;
          end if;
        end loop;
        if K < 10000 and then InArray = True then
          if isPerm(Primes(I), Primes(J)) and then isPerm(Primes(I), K) then
            Answer := Integer'Image(Primes(I))(2..5)&Integer'Image(Primes(J))(2..5)&Integer'Image(K)(2..5);
            goto endProgram;
          end if;
          InArray := False;
        end if;
      end;
    end loop;
  end loop;

  <<endProgram>>
  
  Put_Line("The answer is: "&Answer);
  
end Euler49;