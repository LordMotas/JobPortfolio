--Project Euler #36
--The decimal 585 = 1001001001 (binary), is palindromic in both bases
--Find the sum of all numbers, less than one million,
--which are palindromic in base 10 and base 2
--(Leading zeroes are not included)

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler36 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  function binary (E : Natural) return string is 
    Char : Character;
  begin
    if E = 0 then 
      return "";
    else 
      if E mod 2 = 0 then
        Char := '0';
      else
        Char := '1';
      end if;
      return binary(E/2) & Char;
    end if;
  end binary;

  function isPalindrome (I : Integer) return Boolean is
    S : SU.Unbounded_String := SU.To_Unbounded_String(Integer'Image(I));
    Text : String := SU.To_String(S)(2..Length(S));
  begin
    for Offset in 0..Text'Length / 2 - 1 loop
      if Text (Text'First + Offset) /= Text (Text'Last - Offset) then
        return False;
      end if;
    end loop;
    return True;
  end isPalindrome;

  function isPalindrome (S : SU.Unbounded_String) return Boolean is
    Text : String := SU.To_String(S)(1..Length(S));
  begin
    for Offset in 0..Text'Length / 2 - 1 loop
      if Text (Text'First + Offset) /= Text (Text'Last - Offset) then
        return False;
      end if;
    end loop;
    return True;
  end isPalindrome;

  --Variable Declarations
  Answer : Integer := 0;

begin

  for I in 1..1000000 loop
    if isPalindrome(I) then
      --Check if the original is a palindrome
      if isPalindrome(SU.To_Unbounded_String(Binary(I))) then
        --If so, add to the Answer
        Answer := Answer + I;
      end if;
    end if;
  end loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler36;