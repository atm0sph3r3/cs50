<?php

class Entry {
    
    private $controller = NULL;
    private $method = NULL;
    private $arg1 = NULL;
    private $concreteController = NULL;
    
    public function __construct() {
        //Split URL
        $this->splitUrl();
        //Create a concret controller
        $this->createController();
        //Call the specified method if possible
        $this->callMethod();
    }
    
    //Call a valid method if possible
    private function callMethod(){
         if($this->concreteController && $this->method){
            if($this->arg1){
                $this->concreteController->{$this->method}($this->arg1);
            } else {
                $this->concreteController->{$this->method}();
            }
        } else if($this->concreteController){
            //Call the default method in the controller
            $this->concreteController->index();
        }
    }
  
    //Instantiate a controller object
    private function createController(){
        if(file_exists($this->controller . ".php")){
            $this->concreteController = new $this->controller();
        } else {
            $this->concreteController = new Quote();
        }
    }
    
    //Split URL on "/"
    private function splitUrl(){
        //Filter REQUEST_URI
        $url = isset($_GET['url'])?filter_var($_GET['url'],FILTER_SANITIZE_URL):NULL;
        if($url){
            $explodeUrl = explode("/",$url);
            $this->controller = isset($explodeUrl[0]) ? $explodeUrl[0] : NULL;
            $this->method = isset($explodeUrl[1]) ? $explodeUrl[1]: "index";
            $this->arg1 = isset($explodeUrl[2]) ? $explodeUrl[2] : NULL;
        }
    }
}
