--Project Euler #47
--Find the first four consecutive integers to have four distinct prime factors.
--What is the first of these numbers?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler47 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  function isPrime(N : Integer) return Boolean is
    J : Integer := 2;
  begin
    if N = 2 then
      return True;
    end if;
    if N < 2 then
      return False;
    end if;
    <<PrimeLoop>>
    if N mod J = 0 then
      return False;
    end if;
    J := J + 1;
    if J < N then
      goto PrimeLoop;
    end if;
    return True;
  end isPrime;

  type IntArray is array(1..140000) of Integer;

  function numPrimeFactors(N : Integer; P : IntArray) return Integer is
    Nod : Integer := 0;
    PrimeFactor : Boolean;
    Remain : Integer := N;
  begin
    for I in 1..P'Length - 1 loop
      if P(I) * P(I) > N then
        Nod := Nod + 1;
        return Nod;
      end if;
      PrimeFactor := False;
      while Remain mod P(I) = 0 loop
        PrimeFactor := True;
        Remain := Remain / P(I);
      end loop;
      if PrimeFactor = True then
        Nod := Nod + 1;
      end if;
      if Remain = 1 then
        return Nod;
      end if;
    end loop;
    return 0;
  end numPrimeFactors;

  --Variable Declarations
  Answer : Integer := 2 * 3 * 5 * 7;
  TargetPrimeFactor : Integer := 4;
  TargetConsec : Integer := 4;
  Consec : Integer := 1;
  I : Integer := 1;
  Primes : IntArray;
  Count : Integer := 1;

begin

  <<firstLoop>>
  if isPrime(I) then
    Primes(Count) := I;
    Count := Count + 1; 
  end if;
  I := I + 1;
  if I < 140000 then
    goto firstLoop;
  end if;

  while Consec < TargetConsec loop
    Answer := Answer + 1;
    if numPrimeFactors(Answer, Primes) >= TargetPrimeFactor then
      Consec := Consec + 1;
    else
      Consec := 0;
    end if;
  end loop;

  Put_Line("The answer is: "&Integer'Image(Answer - 3));

end Euler47;