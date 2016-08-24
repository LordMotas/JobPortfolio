--Project Euler #33
--Fraction 49/98 is a curious fraction, as an inexperienced mathematician
--in attempting to simplify it may incorrectly believe that 49/98=4/8,
--which is correct, is obtained by cancelling the 9s.
--There are exactly four non-trivial examples of this type of fraction,
--less than one in value, and containing two digits in the
--numerator and denominator.
--If the product of these four fractions is given in its lowest common terms,
--find the value of the denominator.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler33 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  function gcd(A : Integer; B : Integer) return Integer is
  begin
    if B = 0 then
      return A;
    else
      return gcd(B, A mod B);
    end if;
  end gcd;

  --Variable Declarations
  Answer : Integer := 0;
  DenominatorProduct, NumeratorProduct : Integer := 1;

begin

  for I in 1..9 loop
    for D in 1..I loop
      for N in 1..D loop
        if ((N * 10 + I) * D) = (N * (I * 10 + D)) then
          DenominatorProduct := DenominatorProduct * D;
          NumeratorProduct := NumeratorProduct * N;
        end if;
      end loop;
    end loop;
  end loop;

  Answer := DenominatorProduct / gcd(NumeratorProduct, DenominatorProduct);

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler33;