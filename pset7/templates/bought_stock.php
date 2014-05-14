<? 
if(isset($results)):
    extract($results);
?> 
<div>
    Stock purchased: <?= $symbol ?>
    Shares purchased: <?= $shares ?>
    Share price: <?= numberFormat($price) ?>
    Total cost: <?= numberFormat($cost) ?>
</div>
<?
endif;
?>

