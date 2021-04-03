
                j = 7;
                for ( ii = 0; ii < IN_BITS; ++ii )
                {
                    if ( ii == j )
                    {
                        printf("%d ", arr[ii]);
                        j += 8;
                    }
                    else
                        printf("%d", arr[ii]);
                }
                printf("\n");

