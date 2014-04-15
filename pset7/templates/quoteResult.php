
<? if(isset($quote && $stock)): ?>
    <div>Stock: <?= $stock ?></div>
    <div>Price: <?= $quote ?></div>
<? else: ?>
    <div>No stock found. Please try again.</div>
<? endif; ?>    
