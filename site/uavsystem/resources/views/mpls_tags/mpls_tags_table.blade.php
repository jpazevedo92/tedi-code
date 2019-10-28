<table style="width:100%">
        <thead>
            <tr>
                <th>Tag</th>
                <th>Operations</th>
            </tr>
        </thead>
        <tbody>
        @foreach($mpls_tags as $mpls_tag)

            <tr>
                <td>{{$mpls_tag->tag}}</a></td> 
                <td>
                    <div class="form-group">
                        <form action="{{'/mpls_tags/'.$mpls_tag->id }}" method="post">
                            {{ csrf_field() }}
                            {{method_field('DELETE')}}
                            <a href="{{'/mpls_tags/'.$mpls_tag->id.'/edit' }}" class="btn btn-warning"><i class="fa fa-edit"></i></a>
                            <button type="submit" class="btn btn-danger btn-xl">
                            <i class="fa fa-trash"></i>
                            </button>
                        </form>
                    </div>
            </td>
            </tr>
        @endforeach
        </tbody>
    </table>