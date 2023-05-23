// Copyright 2021 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package issue45985

func app[S interface{ ~[]T }, T any](s S, e T) S {
	return append(s, e)
}

func _() {
	_ = app /* ERROR "int does not match" */ [int]
}
