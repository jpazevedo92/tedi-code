<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Uav extends Model
{
    public function routes()
    {
        return $this->hasMany(Route::class);
    }
    
}
