
<?php foreach($items as $delta => $item) { ?>

<div class="<?php echo $classes; ?>">
    
    <img src="<?php print file_create_url($item['#item']['uri']); ?>" alt="<?php print $item['#item']['alt']; ?>"
         title="<?php print $item['#item']['title']; ?>" />
    
</div>

<?php } ?>