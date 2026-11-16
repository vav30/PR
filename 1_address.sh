
#nano addressbook.sh 
#paste the code
#cntrl+o,enter,cntrl+x
#chmod +x address.sh


#!/bin/bash

while true
do
    echo "1. Create"
    echo "2. View"
    echo "3. Insert"
    echo "4. Delete"
    echo "5. Modify"
    echo "6. Exit"

    read -p "Enter choice: " ch

    case $ch in

    1)
        touch address.txt
        echo "Address Book Created"
        ;;

    2)
        cat address.txt
        ;;

    3)
        read -p "Enter Name: " name
        read -p "Enter Phone: " phone
        echo "$name $phone" >> address.txt
        echo "Record Inserted"
        ;;

    4)
        read -p "Enter Name to Delete: " name
        grep -v "^$name " address.txt > temp.txt
        mv temp.txt address.txt
        echo "Record Deleted"
        ;;

    5)
        read -p "Enter Name to Modify: " name
        grep -v "^$name " address.txt > temp.txt
        mv temp.txt address.txt

        read -p "Enter New Name: " name
        read -p "Enter New Phone: " phone
        echo "$name $phone" >> address.txt
        echo "Record Modified"
        ;;

    6)
        exit
        ;;

    *)
        echo "Invalid Choice"
        ;;

    esac
done
