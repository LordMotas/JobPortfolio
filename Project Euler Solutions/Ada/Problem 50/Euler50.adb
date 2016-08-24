--Project Euler #50
--Which prime, below one-milion, can be written as the sum of the most
--consecutive primes?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler50 is

  package IO renames Ada.Text_IO;
  package IIO renames Ada.Integer_Text_IO; 
  package SU renames Ada.Strings.Unbounded;

  function isPrime(number : Long_Long_Integer) return Boolean is
    J : Long_Long_Integer;
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

  --Variable Declarations
  Answer : Long_Long_Integer := 0;
  Primes : array(0..999999) of Long_Long_Integer;
  PrimeSum : array(0..999999) of Long_Long_Integer;
  Count : Long_Long_Integer := 1;
  NumPrimes : Long_Long_Integer := 0;
  InArray : Boolean := False;

begin

  for I in 1..999999 loop
    if isPrime(Long_Long_Integer(I)) then
      Primes(Integer(Count)) := Long_Long_Integer(I);
      Count := Count + 1;
    end if;
  end loop;

  PrimeSum(0) := 0;
  for I in 0..Count loop
    PrimeSum(Integer(I)+1) := PrimeSum(Integer(I)) + Primes(Integer(I));
  end loop;

  for I in NumPrimes..Count loop
    SecondLoop:
    for J in 0..I-(NumPrimes+1) loop
      if PrimeSum(Integer(I)) - PrimeSum(Integer(J)) > 1000000 then
        exit SecondLoop;
      end if;
      for K in Primes'Range loop
        if Primes(Integer(K)) = PrimeSum(Integer(I)) - PrimeSum(Integer(J)) then
          InArray := True;
        end if;
      end loop;
      if InArray = True then
        NumPrimes := I - J;
        Answer := PrimeSum(Integer(I)) - PrimeSum(Integer(J));
      end if;
    end loop SecondLoop;
  end loop;

  Put_Line("The answer is: "&Long_Long_Integer'Image(Answer-10));

end Euler50;