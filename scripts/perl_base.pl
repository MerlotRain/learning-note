# comment on single line

=pod
pod means Plain Old Documentation
comment on multiple lines - line 1
comment on multiple lines - line 2
cut means cut the comment
=cut

# base variant type

# scaler type

$a = 10; # there is a scaler, named a, it's a integer, and it's value is 10
$b = 10.5; # there is a scaler, named b, it's a float, and it's value is 10.5
$c = 0x1f; # there is a scaler, named c, it's a hex, and it's value is 31
$d = "hello world"; # there is a scaler, named d, it's a string, and it's value is "hello world"

# array type
@array = (1, 2, 3, 4, 5); # there is an array, named array, it's a array, and it's value is (1, 2, 3, 4, 5)
@array2 = (1..10); # there is an array, named array2, it's a array, and it's value is (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

print(@array2);

# hash type
%hash = (a => 1, b => 2, c => 3); # there is a hash, named hash, it's a hash, and it's value is (a => 1, b => 2, c => 3)
%hash2 = (a => 1, b => 2, c => 3, d => 4, e => 5); # there is a hash, named hash2, it's a hash, and it's value is (a => 1, b => 2, c => 3, d => 4, e => 5)

# hash can not use print function 
# only use Data::Dumper;
use Data::Dumper;
print Dumper(\%hash2);

# use foreach 
# `our`: it's mean a global variant
# `my` it's mean a local variant
foreach my $key (keys %hash2) {
    print "$key => $hash2{$key}\n";
}