<div class="<?php echo $classes; ?>">
    <?php if(!$label_hidden) : ?>
    <h3><?php print $label; ?></h3>
    <?php endif; ?>
    <?php foreach($items as $item) :
        print render($item);
    endforeach; ?>
</div>