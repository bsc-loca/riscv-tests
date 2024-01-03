#!/usr/bin/perl -w

(our $usageMsg = <<'ENDMSG') =~ s/^\#//gm;
#
# Simple script which creates an Sparse Matrix using CSR format.
#
ENDMSG

use List::Util qw(shuffle);
use strict "vars";
use warnings;
no  warnings("once");
use Getopt::Long;

#--------------------------------------------------------------------------
# Command line processing
#--------------------------------------------------------------------------

our %opts;

sub usage()
{

  print "\n";
  print " Usage: gendata.pl [options] \n";
  print "\n";
  print " Options:\n";
  print "  --help  print this message\n";
  print "  --nnz   Number of Non-Zero elements [2048]\n";
  print "  --row   Number of rows in the Sparse Matrix [64]\n";
  print "  --col   Number of columns in the Sparse Matrix [512]\n";
  print "  --seed  random seed [1]\n";
  print "  --Dtype Data type [double] \n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{

  $opts{"help"} = 0;
  $opts{"nnz"} = 4096;
  $opts{"row"} = 64;
  $opts{"col"} = 2048;
  $opts{"seed"} = 1;
  $opts{"Dtype"} = "double";
  Getopt::Long::GetOptions( \%opts, 'help|?', 'nnz:i', 'row:i', 'col:i', 'seed:i', 'Dtype:s' ) or usage();
  $opts{"help"} and usage();
  
  my @types=('double');
  unless ( grep( /^$opts{Dtype}$/, @types ) ) {
     print "Error: $opts{Dtype} is an unsupported data type. Valid values are @types\n";
     exit ();
  } 

}

#--------------------------------------------------------------------------
# Helper Functions
#--------------------------------------------------------------------------

sub printArray
{
  my $arrayName = $_[0];
  my $arrayRef  = $_[1];
  my $arraySize = $_[2];
  my $arrayType = $_[3];

  my $numCols = 20;
  my $arrayLen = scalar(@{$arrayRef});

  print  "static ".$arrayType." ".$arrayName."[".$arraySize."] = \n";
  print  "{\n";

  if ( $arrayLen <= $numCols ) {
    print  "  ";
    for ( my $i = 0; $i < $arrayLen; $i++ ) {
      print  sprintf("%g",$arrayRef->[$i]);
      if ( $i != $arrayLen-1 ) {
        print  ", ";
      }
    }
    print  "\n";
  }

  else {
    my $numRows = int($arrayLen/$numCols);
    for ( my $j = 0; $j < $numRows; $j++ ) {
      print  "  ";
      for ( my $i = 0; $i < $numCols; $i++ ) {
        my $index = $j*$numCols + $i;
        print  sprintf("%g",$arrayRef->[$index]);
        if ( $index != $arrayLen-1 ) {
          print  ", ";
        }
      }
      print  "\n";
    }

    if ( $arrayLen > ($numRows*$numCols) ) {
      print  "  ";
      for ( my $i = 0; $i < ($arrayLen-($numRows*$numCols)); $i++ ) {
        my $index = $numCols*$numRows + $i;
        print  sprintf("%g",$arrayRef->[$index]);
        if ( $index != $arrayLen-1 ) {
          print  ", ";
        }
      }
      print  "\n";
    }

  }

  print   "};\n\n";
}

# Function to distribute elements non-uniformly among containers
sub distribute_non_uniformly {
    my ($total_elements, $num_containers, $max) = @_;

    my @containers = ();  # Array to store the number of elements in each container
    my @cont_id; ## random containers
    
    for my $i (0 .. $num_containers-2) {
        push @cont_id, $i;
        push @containers, 0;
    }
    @cont_id = shuffle(@cont_id);

    # Distribute elements non-uniformly among containers
    for (my $i = 0; $i < $num_containers - 1; $i++) {
        # Generate a random number of elements for the current container
        my $elements = int(rand($total_elements / 8)) + 1;
        
        # Ensure it doesn't exceed the remaining total number of elements
        $elements = $total_elements if $elements > $total_elements;
        
        if ($elements >= $max ) {
            print "Error: The number of columns is not enough, please increase and try again. \n";
            exit ();
        } 
        
        # Subtract the assigned elements from the total and store in the container
        $total_elements -= $elements;
        splice (@containers,$cont_id[$i],1,$elements);
    }

    # The last container gets the remaining elements
    push @containers, $total_elements;

    return @containers;
}

sub get_pointers {
    my ($nnz_per_rows, $nrow) = @_;
    my @pointers = ();
    my $ptr;  

    $ptr->[0] = 0;
    push( @pointers, $ptr->[0] );
    my $nnz_sum = $nnz_per_rows->[0]; 
    for ( my $i = 1; $i < $nrow; $i++ ) {   
        $ptr->[$i] = $nnz_sum ;
        $nnz_sum += $nnz_per_rows->[$i];
        push( @pointers, $ptr->[$i] );
    }
    $ptr->[$nrow] = $nnz_sum ;
    push( @pointers, $ptr->[$nrow] );

    return @pointers;
}

sub fill_vector {
    my ($size, $option) = @_;

    my @vector = ();
    my $val;
    
    my $in_max =100; 
    
    for ( my $i = 0; $i < $size; $i++ ) {   
        if ($option eq 'random') {
            $val->[$i] = int(rand($in_max));
        }
        else {
            $val->[$i] = int($option);
        }
        push( @vector, $val->[$i] );
    }

    return @vector;
}

# Function to generate non-repeating random numbers
sub random_and_sort_numbers {
    my ($max, $count) = @_;
    
    my @selected_numbers;
    
    while (@selected_numbers < $count) {
        my $random_number = int(rand($max));  # Generate a random number between $start and $end
        
        # Check if the number is already selected
        unless (grep { $_ == $random_number } @selected_numbers) {
            push @selected_numbers, $random_number;  # Add the number to the list of selected numbers
        }
    }
    # Sort the selected numbers
    @selected_numbers = sort {$a <=> $b} @selected_numbers;
    
    return @selected_numbers;
}

sub get_columns {
    my ($nnz_per_rows, $nrow, $ncol) = @_;
    my @columns;

    my @cols;
    for ( my $i = 0; $i < $nrow; $i++ ) {
        @cols=random_and_sort_numbers($ncol,$nnz_per_rows->[$i]);
        for ( my $k = 0; $k < $nnz_per_rows->[$i]; $k++ ){
            push( @columns, $cols[$k] );
        }
        splice @cols;
    }
    return @columns
}

sub spmv{
    my($ptr,$col,$val,$x,$nrow) = @_;
    my @y;

    for (my $row = 0; $row < $nrow; $row++) {
        my $sum = 0;
        for (my $idx = $ptr->[$row]; $idx < $ptr->[$row+1]; $idx++) {
            $sum += $val->[$idx] * $x->[$col->[$idx]];
        }
        push(@y,$sum);
    }
    return @y
}

#--------------------------------------------------------------------------
# Main
#--------------------------------------------------------------------------

sub main()
{
    processCommandLine();
    srand($opts{"seed"});

    my @VAL;
    my @PTR;
    my @COL;
    my @X;
    my @Y;
    my @REF;
    
    # Distribute nnz elements non-uniformly among all rows
    my @nnz_per_row = distribute_non_uniformly($opts{"nnz"},$opts{"row"},$opts{"col"});

    @VAL = fill_vector($opts{"nnz"},"random"); 
    @X   = fill_vector($opts{"col"},"1"); 
    @Y   = fill_vector($opts{"row"},"0");  
    @PTR = get_pointers(\@nnz_per_row,$opts{"row"});
    @COL = get_columns(\@nnz_per_row,$opts{"row"},$opts{"col"});
    @REF = spmv(\@PTR, \@COL, \@VAL, \@X, $opts{"row"}); 

    #Display header file

    print  "#ifndef __DATASET_H \n";
    print  "#define __DATASET_H\n\n";
    print  "#define NROW ".($opts{"row"})." \n";
    print  "#define NCOL ".($opts{"col"})." \n";
    print  "#define NNZ " .($opts{"nnz"})." \n\n";
    
    print  "#define DATA_TYPE \n\n";
    
    print  "typedef $opts{Dtype} data_t;\n\n";

    printArray( "ptr", \@PTR, "NROW+1", "long" );
    printArray( "col", \@COL, "NNZ", "long" );
    printArray( "val", \@VAL, "NNZ", "data_t" );
    printArray( "x", \@X, "NCOL", "data_t" );
    printArray( "y", \@Y, "NROW", "data_t" );
    printArray( "ref", \@REF, "NROW", "data_t" );

    print  "\n#endif //__DATASET_H\n";

}

main();

