# This file was automatically generated by SWIG
package YN00;
require Exporter;
require DynaLoader;
@ISA = qw(Exporter DynaLoader);
package YN00c;
bootstrap YN00;
package YN00;
@EXPORT = qw( );

# ---------- BASE METHODS -------------

package YN00;

sub TIEHASH {
    my ($classname,$obj) = @_;
    return bless $obj, $classname;
}

sub CLEAR { }

sub FIRSTKEY { }

sub NEXTKEY { }

sub FETCH {
    my ($self,$field) = @_;
    my $member_func = "swig_${field}_get";
    $self->$member_func();
}

sub STORE {
    my ($self,$field,$newval) = @_;
    my $member_func = "swig_${field}_set";
    $self->$member_func($newval);
}

sub this {
    my $ptr = shift;
    return tied(%$ptr);
}


# ------- FUNCTION WRAPPERS --------

package YN00;

*cal_kaks = *YN00c::cal_kaks;

# ------- VARIABLE STUBS --------

package YN00;

1;
