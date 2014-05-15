<?
require("../includes/config.php");
if($_SERVER["REQUEST_METHOD"] == "POST"){
    if(($userInfo = $user->info()) !== FALSE){
        extract($_POST);
        if(!empty($current) && !empty($new) && !empty($confirm)){
            if($userInfo[0]["hash"] == crypt($current, $userInfo[0]["hash"])){
                if($new == $confirm){
                    $user->changePassword($_POST["new"]);
                    render("changed_settings.php",array("title"=>"Settings have been updated."));
                } else {
                    apologize("Passwords do not match. Try again.");
                }
            } else {
                apologize("Invalid password. Try again.");
            }
        } else {
            apologize("Ensure fields have been completely filled out before continuing.");
        }
        
    } else {
        apologize("An error has occurred. Please try again.");
    }
    
    
} else {
    render("change_settings.php",array("title"=>"Change personal settings"));
}

